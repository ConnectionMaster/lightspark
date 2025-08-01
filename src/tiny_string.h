/**************************************************************************
    Lightspark, a free flash player implementation

    Copyright (C) 2012-2013  Alessandro Pignotti (a.pignotti@sssup.it)

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
**************************************************************************/

#ifndef TINY_STRING_H
#define TINY_STRING_H 1

#include <cstring>
#include <cctype>
#include <cstdint>
#include <ostream>
#include <limits>
#include <list>
#include "compat.h"
#include <functional>

#include "utils/optional.h"
#include "utils/type_traits.h"

/* forward declare for tiny_string conversion */
typedef unsigned char xmlChar;

namespace lightspark
{

class tiny_string;

template<typename T, EnableIf<std::is_unsigned<T>::value, bool> = false>
inline T convertToNumber(const tiny_string& str);
template<typename T, EnableIf<std::is_signed<T>::value, bool> = false>
inline T convertToNumber(const tiny_string& str);
template<typename T, EnableIf<std::is_floating_point<T>::value, bool> = false>
inline T convertToNumber(const tiny_string& str);

/* Iterates over utf8 characters */
class CharIterator /*: public forward_iterator<uint32_t>*/
{
friend class tiny_string;
private:
	char* buf_ptr;
	uint32_t getChar() const
	{
		if ((*buf_ptr & 0x80)==0x00)
			return uint32_t(*buf_ptr);
		if ((*buf_ptr & 0xe0)==0xc0)
			return ((uint32_t(*buf_ptr) << 6) & 0x7ff)
				+ (uint32_t(*(buf_ptr+1)) & 0x3f);
		if ((*buf_ptr & 0xf0)==0xe0)
			return ((uint32_t(*buf_ptr) << 12) & 0xffff)
				+ ((uint32_t(*(buf_ptr+1)) << 6) & 0xfff)
				+ (uint32_t(*(buf_ptr+2)) & 0x3f);
		if ((*buf_ptr & 0xf8)==0xf0)
			return ((uint32_t(*buf_ptr) << 18) & 0x1fffff)
				+ ((uint32_t(*(buf_ptr+1)) << 12) & 0x3ffff)
				+ ((uint32_t(*(buf_ptr+2)) << 6) & 0xfff)
				+ (uint32_t(*(buf_ptr+3)) & 0x3f);
		return UINT32_MAX;
	}
public:
	CharIterator() : buf_ptr(nullptr) {}
	CharIterator(char* buf) : buf_ptr(buf) {}
	/* Return the utf8-character value */
	uint32_t operator*() const
	{
		return getChar();
	}
	CharIterator& operator++() //prefix
	{
		if (*buf_ptr & 0x80)
		{
			if ((*buf_ptr & 0xf8)==0xf0)
				buf_ptr+=4;
			else if ((*buf_ptr & 0xf0)==0xe0)
				buf_ptr+=3;
			else if ((*buf_ptr & 0xe0)==0xc0)
				buf_ptr+=2;
			else
				++buf_ptr;
		}
		else
			++buf_ptr;
		return *this;
	}
	CharIterator operator++(int) // postfix
	{
		CharIterator result = *this;
		++(*this);
		return result;
	}
	bool operator==(const CharIterator& o) const
	{
		return buf_ptr == o.buf_ptr;
	}
	bool operator!=(const CharIterator& o) const { return !(*this == o); }
	/* returns true if the current character is a digit */
	bool isdigit() const
	{
		return ::isdigit(*buf_ptr);
	}
	/* return the value of the current character interpreted as decimal digit,
	 * i.e. '7' -> 7
	 */
	int32_t digit_value() const
	{
		return *buf_ptr-'0';
	}

	/* returns true if the current character is a digit */
	bool isxdigit() const
	{
		return ::isxdigit(*buf_ptr);
	}
	/* return the value of the current character interpreted as hexadecimal digit,
	 * i.e. '7' -> 7, 'a' -> 10
	 * expects the character to be a valid hex digit
	 */
	int32_t hex_value() const
	{
		switch (*buf_ptr)
		{
			case 'a':
			case 'b':
			case 'c':
			case 'd':
			case 'e':
			case 'f':
				return uint8_t(*buf_ptr)-'a'+10;
			case 'A':
			case 'B':
			case 'C':
			case 'D':
			case 'E':
			case 'F':
				return uint8_t(*buf_ptr)-'A'+10;
			default:
				return digit_value();
		}
	}
	bool isValid() const { return buf_ptr; }
	inline char* ptr() const { return buf_ptr; }
	bool isValidUTF8() const
	{
		return getChar() != UINT32_MAX;
	}
};

/*
 * String class.
 * The string can contain '\0's, so don't use raw_buf().
 * Use len() to determine actual size.
 */
class DLL_PUBLIC tiny_string
{
friend std::ostream& operator<<(std::ostream& s, const tiny_string& r);
friend struct std::hash<lightspark::tiny_string>;
private:
	enum TYPE { READONLY=0, STATIC, DYNAMIC };
	/*must be at least 6 bytes for tiny_string(uint32_t c) constructor */
	#define STATIC_SIZE 64
	char _buf_static[STATIC_SIZE];
	char* buf;
	/*
	   stringSize includes the trailing \0
	*/
	uint32_t stringSize;
	uint32_t numchars;
	TYPE type;
#ifdef MEMORY_USAGE_PROFILING
	//Implemented in memory_support.cpp
	DLL_PUBLIC void reportMemoryChange(int32_t change) const;
#else
	//NOP
	void reportMemoryChange(int32_t change) const {}
#endif
	//TODO: use static buffer again if reassigning to short string
	void makePrivateCopy(const char* s);
	void createBuffer(uint32_t s);
	void resizeBuffer(uint32_t s);
	void resetToStatic();
	void getTrimPositions(uint32_t& start, uint32_t &end) const;
	void init();
	bool isASCII:1;
	bool hasNull:1;
	bool isInteger:1;
public:
	static const uint32_t npos = (uint32_t)(-1);

	tiny_string():_buf_static(),buf(_buf_static),stringSize(1),numchars(0),type(STATIC)
		,isASCII(true),hasNull(false),isInteger(false)
	{
		buf[0]=0;
	}
	/* construct from utf character */
	static tiny_string fromChar(uint32_t c);
	tiny_string(const char* s,bool copy=false);
	tiny_string(const tiny_string& r);
	tiny_string(const std::string& r);
	tiny_string(std::istream& in, int len);
	~tiny_string();
	uint32_t operator[](size_t i) const { return charAt(i); }
	tiny_string& operator=(const tiny_string& s);
	tiny_string& operator=(const std::string& s);
	tiny_string& operator=(const char* s);
	tiny_string& operator+=(const char* s);
	tiny_string& operator+=(const tiny_string& r);
	tiny_string& operator+=(const std::string& s);
	tiny_string& operator+=(uint32_t c);
	const tiny_string operator+(const tiny_string& r) const;
	const tiny_string operator+(const char* s) const;
	const tiny_string operator+(const std::string& r) const;
	bool operator<(const tiny_string& r) const;
	bool operator>(const tiny_string& r) const;
	bool operator==(const tiny_string& r) const;
	bool operator==(const std::string& r) const;
	bool operator!=(const std::string& r) const;
	bool operator!=(const tiny_string& r) const;
	bool operator==(const char* r) const;
	bool operator==(const xmlChar* r) const;
	bool operator!=(const char* r) const;
	inline const char* raw_buf() const
	{
		return buf;
	}
	inline bool empty() const
	{
		return stringSize == 1;
	}
	inline void clear()
	{
		resetToStatic();
		numchars = 0;
		isASCII = true;
		hasNull = false;
		isInteger = false;
	}
	
	/* returns the length in bytes, not counting the trailing \0 */
	inline uint32_t numBytes() const
	{
		return stringSize-1;
	}
	/* returns the length in utf-8 characters, not counting the trailing \0 */
	inline uint32_t numChars() const
	{
		return numchars;
	}
	inline bool isSinglebyte() const
	{
		return isASCII;
	}
	inline bool hasNullEntries() const
	{
		return hasNull;
	}
	inline bool isIntegerValue() const
	{
		return isInteger;
	}
	inline void checkValidUTF()
	{
		if (!isASCII)
		{
			CharIterator it = this->begin();
			bool isvalid = true;
			while (it != this->end())
			{
				if (!it.isValidUTF8())
				{
					isvalid=false;
					break;
				}
				it++;
			}
			if (!isvalid)
			{
				// string is not valid UTF8, we treat it as ascii
				isASCII = true;
				numchars = stringSize-1;
			}
		}
	}

	// Returns a string with the supplied prefix removed, if found,
	// otherwise it returns the original string.
	tiny_string stripPrefix(const tiny_string& prefix, size_t offset = 0) const;
	// Returns a string with the supplied sufffix removed, if found,
	// otherwise it returns the original string.
	tiny_string stripSuffix(const tiny_string& suffix, size_t offset = 0) const;
	
	/* start and len are indices of utf8-characters */
	tiny_string substr(uint32_t start, uint32_t len) const;
	tiny_string substr(uint32_t start, const CharIterator& end) const;
	/* start and len are indices of bytes */
	tiny_string substr_bytes(uint32_t start, uint32_t len, bool resultisascii=false) const;
	/* finds the first occurence of char in the utf-8 string
	 * Return NULL if not found, else ptr to beginning of first occurence of c */
	char* strchr(uint32_t c) const;
	char* strchrr(uint32_t c) const;
	/*explicit*/ operator std::string() const;

	FORCE_INLINE void setValue(const char* s,int _numbytes, int _numchars, bool _isASCII, bool _hasNull, bool _isInteger, bool copy)
	{
		if(copy)
		{
			resetToStatic();
			stringSize=_numbytes+1;
			if(stringSize > STATIC_SIZE)
				createBuffer(stringSize);
			memcpy(buf,s,_numbytes);
			buf[_numbytes]=0;
		}
		else
		{
			if(type==DYNAMIC)
			{
				reportMemoryChange(-stringSize);
				delete[] buf;
			}
			type=READONLY;
			stringSize=_numbytes+1;
			buf=(char*)s;
		}
		numchars=_numchars;
		isASCII=_isASCII;
		hasNull=_hasNull;
		isInteger=_isInteger;
	}
	static uint32_t unicodeToUTF8(uint32_t c,char* buf);
	static bool unicodeIsWhiteSpace(uint32_t c);
	FORCE_INLINE void setChar(uint32_t c)
	{
		if (type != STATIC)
			resetToStatic();
		isASCII = c<0x80;
		if (isASCII)
		{
			buf[0] = c&0xff;
			stringSize = 2;
		}
		else
			stringSize = unicodeToUTF8(c,buf);
		buf[stringSize-1] = '\0';
		hasNull = c == 0;
		isInteger = c >= '0' && c <= '9';
		numchars = 1;
	}
	
	bool contains(const tiny_string& str) const;
	bool contains(uint32_t ch) const;
	bool startsWith(const tiny_string& str) const;
	bool endsWith(const tiny_string& str) const;
	bool startsWith(const char* o) const;
	bool endsWith(const char* o) const;
	/* idx is an index of utf-8 characters */
	uint32_t charAt(uint32_t idx) const
	{
		if (isASCII)
			return buf[idx];
		auto it = this->begin();
		uint32_t i = 0;
		while (i++ < idx)
		{
			++it;
		}
		return *it;
	}
	/* start is an index of characters.
	 * returns index of character */
	uint32_t find(const tiny_string& needle, uint32_t start = 0) const;
	uint32_t rfind(const tiny_string& needle, uint32_t start = npos) const;
	uint32_t findFirst(const tiny_string& str, uint32_t start = 0) const;
	uint32_t findFirstInv(const tiny_string& str, uint32_t start = 0) const;
	uint32_t findLast(const tiny_string& str, uint32_t start = npos) const;
	uint32_t findLastInv(const tiny_string& str, uint32_t start = npos) const;
	// fills line with the text from byteindex up to the next line terminator
	// upon return byteindex will be set to the index after the next line terminator
	// returns true if a line terminator was found
	bool getLine(uint32_t& byteindex, tiny_string& line);
	tiny_string& replace(uint32_t pos1, uint32_t n1, const tiny_string& o);
	tiny_string& replace_bytes(uint32_t bytestart, uint32_t bytenum, const tiny_string& o);
	tiny_string lowercase() const;
	tiny_string uppercase() const;
	/* like strcasecmp(s1.raw_buf(),s2.raw_buf()) but for unicode */
	int strcasecmp(tiny_string& s2) const;
	// Compares two strings for equality, ignoring case, done in a way
	// that matches Flash Player's behaviour.
	bool caselessEquals(const tiny_string& str) const;
	// Compares two strings for equality, with the specified case
	// sensitivity.
	bool equalsWithCase(const tiny_string& str, bool caseSensitive) const;
	/* split string at each occurrence of delimiter character */
	std::list<tiny_string> split(uint32_t delimiter) const;
	/* Convert from byte offset to UTF-8 character index */
	uint32_t bytePosToIndex(uint32_t bytepos) const;
	/* iterate over utf8 characters */
	CharIterator begin();
	CharIterator begin() const;
	CharIterator end();
	CharIterator end() const;
	int compare(const tiny_string& r) const;
	template<typename T, EnableIf<std::is_arithmetic<T>::value, bool> = false>
	bool toNumber(T& value) const
	{
		try
		{
			value = convertToNumber<T>(*this);
			return true;
		}
		catch (std::exception&)
		{
			return false;
		}
	}
	template<typename T, EnableIf<std::is_arithmetic<T>::value, bool> = false>
	Optional<T> tryToNumber() const
	{
		try
		{
			return convertToNumber<T>(*this);
		}
		catch (std::exception&)
		{
			return {};
		}
	}
	tiny_string toQuotedString() const;
	// returns string that has whitespace characters removed at begin and end
	tiny_string removeWhitespace() const;
	// Returns a string with all repeated instances of `ch` removed from
	// the beginning of the string.
	tiny_string trimStartMatches(uint32_t ch) const;
	// Returns a string with all repeated instances of `str` removed from
	// the beginning of the string.
	tiny_string trimStartMatches(const tiny_string& str) const;
	// returns string that has whitespace characters removed at begin
	tiny_string trimLeft() const;
	// returns true if the string is empty or only contains whitespace characters
	bool isWhiteSpaceOnly() const;
	// returns string that has consecutive whitespace characters compacted to one space only
	tiny_string compactHTMLWhiteSpace(bool trimleft, bool* hasNewline=nullptr) const;
	bool endsWithHTMLWhitespace() const;

	// encodes all null bytes instring to xml notation ("&#x0;")
	tiny_string encodeNull() const;
	// returns start/end byte position from character index/length pair
	void getByteRange(uint32_t start, uint32_t len, uint32_t& bytestart, uint32_t& byteend) const;
};

template<typename T, EnableIf<std::is_unsigned<T>::value, bool>>
inline T convertToNumber(const tiny_string& str)
{
	auto num = std::stoull(str);
	if (num > std::numeric_limits<T>::max())
		throw std::out_of_range("Converted number is too big for T");
	return num;
}

template<typename T, EnableIf<std::is_signed<T>::value, bool>>
inline T convertToNumber(const tiny_string& str)
{
	auto num = std::stoll(str);
	if (num > std::numeric_limits<T>::max())
		throw std::out_of_range("Converted number is too big for T");
	if (num < std::numeric_limits<T>::min())
		throw std::out_of_range("Converted number is too small for T");
	return num;
}

template<typename T, EnableIf<std::is_floating_point<T>::value, bool>>
inline T convertToNumber(const tiny_string& str)
{
	auto num = std::stold(str);
	if (num > std::numeric_limits<T>::max())
		throw std::out_of_range("Converted number is too big for T");
	if (num < std::numeric_limits<T>::lowest())
		throw std::out_of_range("Converted number is too small for T");
	return num;
}

}
namespace std
{
// using djb2 hash function from http://www.cse.yorku.ca/~oz/hash.html
template <>
struct hash<lightspark::tiny_string>
{
	size_t operator()(const lightspark::tiny_string& s) const
	{
		size_t hash = 5381;
		uint32_t n =0;
		while (n++ < s.stringSize-1)
			hash = ((hash << 5) + hash) + s.buf[n]; /* hash * 33 + c */
		return hash;
	}
};
}
#endif /* TINY_STRING_H */
