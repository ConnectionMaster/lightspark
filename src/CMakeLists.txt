#**************************************************************************
#    Lightspark, a free flash player implementation
#
#    Copyright (C) 2010-2013  Alessandro Pignotti <a.pignotti@sssup.it>
#    Copyright (C) 2010  Giacomo Spigler <g.spigler@sssup.it>
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU Lesser General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#   This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU Lesser General Public License for more details.
#
#   You should have received a copy of the GNU Lesser General Public License
#   along with this program.  If not, see <http://www.gnu.org/licenses/>.
#**************************************************************************

# liblightspark.so sources
SET(LIBSPARK_SOURCES
  allclasses.cpp
  asobject.cpp
  compat.cpp
  logger.cpp
  memory_support.cpp
  swf.cpp
  swftypes.cpp
  thread_pool.cpp
  threading.cpp
  timer.cpp
  tiny_string.cpp
  errorconstants.cpp
  launcher.cpp
  backends/audio.cpp
  backends/builtindecoder.cpp
  backends/cachedsurface.cpp
  backends/config.cpp
  backends/currency.cpp
  backends/decoder.cpp
  backends/event_loop.cpp
  backends/extscriptobject.cpp
  backends/geometry.cpp
  backends/graphics.cpp
  backends/image.cpp
  backends/input.cpp
  backends/locale.cpp
  backends/netutils.cpp
  backends/rendering.cpp
  backends/rendering_context.cpp
  backends/rtmputils.cpp
  backends/security.cpp
  backends/sdl/event_loop.cpp
  backends/streamcache.cpp
  backends/urlutils.cpp
  backends/xml_support.cpp
  parsing/amf3_generator.cpp
  parsing/config.cpp
  parsing/crossdomainpolicy.cpp
  parsing/flv.cpp
  parsing/streams.cpp
  parsing/tags.cpp
  parsing/tags_stub.cpp
  parsing/textfile.cpp
  scripting/abc.cpp
  scripting/abc_avm1.cpp
  scripting/abc_flashaccessibility.cpp
  scripting/abc_flashdesktop.cpp
  scripting/abc_flashconcurrent.cpp
  scripting/abc_flashcrypto.cpp
  scripting/abc_flashdisplay.cpp
  scripting/abc_flashdisplay3d.cpp
  scripting/abc_flashevents.cpp
  scripting/abc_flasherrors.cpp
  scripting/abc_flashexternal.cpp
  scripting/abc_flashfilesystem.cpp
  scripting/abc_flashfilters.cpp
  scripting/abc_flashgeom.cpp
  scripting/abc_flashglobalization.cpp
  scripting/abc_flashmedia.cpp
  scripting/abc_flashnet.cpp
  scripting/abc_flashprinting.cpp
  scripting/abc_flashprofiler.cpp
  scripting/abc_flashsampler.cpp
  scripting/abc_flashsecurity.cpp
  scripting/abc_flashsensors.cpp
  scripting/abc_flashsystem.cpp
  scripting/abc_flashtext.cpp
  scripting/abc_flashui.cpp
  scripting/abc_flashutils.cpp
  scripting/abc_flashxml.cpp
  scripting/abc_avmplus.cpp
  scripting/abc_toplevel.cpp
  scripting/abc_codesynt.cpp
  scripting/abc_fast_interpreter.cpp
  scripting/abc_interpreter.cpp
  scripting/abc_interpreter_helper.cpp
  scripting/abc_interpreter_preload_callproperty.cpp
  scripting/abc_interpreter_preload_dup.cpp
  scripting/abc_interpreter_preload_getlex.cpp
  scripting/abc_interpreter_preload_getproperty.cpp
  scripting/abc_interpreter_preload_setproperty.cpp
  scripting/abc_methods.cpp
  scripting/abc_methods_optimized.cpp
  scripting/abc_methods_optimized_add.cpp
  scripting/abc_methods_optimized_bitnot.cpp
  scripting/abc_methods_optimized_callproperty.cpp
  scripting/abc_methods_optimized_coerce_s.cpp
  scripting/abc_methods_optimized_convert_s.cpp
  scripting/abc_methods_optimized_getproperty.cpp
  scripting/abc_methods_optimized_getslot.cpp
  scripting/abc_methods_optimized_newcatch.cpp
  scripting/abc_methods_optimized_negate.cpp
  scripting/abc_methods_optimized_functionbuiltin.cpp
  scripting/abc_methods_optimized_functionsynthetic.cpp
  scripting/abc_methods_optimized_setproperty.cpp
  scripting/abc_methods_optimized_setslot.cpp
  scripting/abc_optimizer.cpp
  scripting/abc_opcodes.cpp
  scripting/abctypes.cpp
  scripting/flash/accessibility/flashaccessibility.cpp
  scripting/flash/globalization/stringtools.cpp
  scripting/flash/concurrent/Mutex.cpp
  scripting/flash/concurrent/Condition.cpp
  scripting/flash/crypto/flashcrypto.cpp
  scripting/flash/desktop/clipboardformats.cpp
  scripting/flash/desktop/clipboardtransfermode.cpp
  scripting/flash/desktop/flashdesktop.cpp
  scripting/flash/display/BitmapContainer.cpp
  scripting/flash/display/BitmapData.cpp
  scripting/flash/display/Bitmap.cpp
  scripting/flash/display/bitmapencodingcolorspace.cpp
  scripting/flash/display/colorcorrection.cpp
  scripting/flash/display/ColorCorrectionSupport.cpp
  scripting/flash/display/DisplayObject.cpp
  scripting/flash/display/IBitmapDrawable.cpp
  scripting/flash/display/flashdisplay.cpp
  scripting/flash/display/FrameContainer.cpp
  scripting/flash/display/TokenContainer.cpp
  scripting/flash/display/Graphics.cpp
  scripting/flash/display/GraphicsBitmapFill.cpp
  scripting/flash/display/GraphicsEndFill.cpp
  scripting/flash/display/GraphicsGradientFill.cpp
  scripting/flash/display/GraphicsPath.cpp
  scripting/flash/display/GraphicsShaderFill.cpp
  scripting/flash/display/GraphicsSolidFill.cpp
  scripting/flash/display/GraphicsStroke.cpp
  scripting/flash/display/GraphicsTrianglePath.cpp
  scripting/flash/display/Loader.cpp
  scripting/flash/display/LoaderInfo.cpp
  scripting/flash/display/MorphShape.cpp
  scripting/flash/display/MovieClip.cpp
  scripting/flash/display/NativeMenuItem.cpp
  scripting/flash/display/NativeWindow.cpp
  scripting/flash/display/RootMovieClip.cpp
  scripting/flash/display/Shape.cpp
  scripting/flash/display/SimpleButton.cpp
  scripting/flash/display/Stage.cpp
  scripting/flash/display/Stage3D.cpp
  scripting/flash/display/jpegencoderoptions.cpp
  scripting/flash/display/jpegxrencoderoptions.cpp
  scripting/flash/display/pngencoderoptions.cpp
  scripting/flash/display/shaderparametertype.cpp
  scripting/flash/display/shaderprecision.cpp
  scripting/flash/display/swfversion.cpp
  scripting/flash/display/triangleculling.cpp
  scripting/flash/display/StageAspectRatio.cpp
  scripting/flash/display3d/flashdisplay3d.cpp
  scripting/flash/display3d/flashdisplay3dtextures.cpp
  scripting/flash/events/flashevents.cpp
  scripting/flash/events/FocusEvent.cpp
  scripting/flash/events/HttpStatusEvent.cpp
  scripting/flash/external/ExternalInterface.cpp
  scripting/flash/external/ExtensionContext.cpp
  scripting/flash/filters/flashfilters.cpp
  scripting/flash/filters/BevelFilter.cpp
  scripting/flash/filters/BlurFilter.cpp
  scripting/flash/filters/ColorMatrixFilter.cpp
  scripting/flash/filters/ConvolutionFilter.cpp
  scripting/flash/filters/DisplacementMapFilter.cpp
  scripting/flash/filters/DropShadowFilter.cpp
  scripting/flash/filters/GlowFilter.cpp
  scripting/flash/filters/GradientBevelFilter.cpp
  scripting/flash/filters/GradientGlowFilter.cpp
  scripting/flash/filesystem/flashfilesystem.cpp
  scripting/flash/geom/flashgeom.cpp
  scripting/flash/geom/Matrix3D.cpp
  scripting/flash/geom/orientation3d.cpp
  scripting/flash/geom/Point.cpp
  scripting/flash/geom/Rectangle.cpp
  scripting/flash/geom/Vector3D.cpp
  scripting/flash/globalization/datetimeformatter.cpp
  scripting/flash/globalization/datetimestyle.cpp
  scripting/flash/globalization/lastoperationstatus.cpp
  scripting/flash/globalization/localeid.cpp
  scripting/flash/globalization/currencyformatter.cpp
  scripting/flash/globalization/currencyparseresult.cpp
  scripting/flash/globalization/numberformatter.cpp
  scripting/flash/globalization/numberparseresult.cpp
  scripting/flash/globalization/collator.cpp
  scripting/flash/globalization/collatormode.cpp
  scripting/flash/globalization/datetimenamecontext.cpp
  scripting/flash/globalization/datetimenamestyle.cpp
  scripting/flash/globalization/nationaldigitstype.cpp
  scripting/flash/media/flashmedia.cpp
  scripting/flash/media/audiodecoder.cpp
  scripting/flash/media/audiooutputchangereason.cpp
  scripting/flash/media/avnetworkingparams.cpp
  scripting/flash/media/avtagdata.cpp
  scripting/flash/media/h264level.cpp
  scripting/flash/media/h264profile.cpp
  scripting/flash/media/id3info.cpp
  scripting/flash/media/microphoneenhancedmode.cpp
  scripting/flash/media/microphoneenhancedoptions.cpp
  scripting/flash/media/soundcodec.cpp
  scripting/flash/media/stagevideoavailabilityreason.cpp
  scripting/flash/media/videodecoder.cpp
  scripting/flash/net/flashnet.cpp
  scripting/flash/net/FileReference.cpp
  scripting/flash/net/FileReferenceList.cpp
  scripting/flash/net/LocalConnection.cpp
  scripting/flash/net/netgroupreceivemode.cpp
  scripting/flash/net/netgroupreplicationstrategy.cpp
  scripting/flash/net/netgroupsendmode.cpp
  scripting/flash/net/netgroupsendresult.cpp
  scripting/flash/net/URLRequestHeader.cpp
  scripting/flash/net/URLStream.cpp
  scripting/flash/net/Socket.cpp
  scripting/flash/net/XMLSocket.cpp
  scripting/flash/net/NetStreamInfo.cpp
  scripting/flash/net/NetStreamPlayOptions.cpp
  scripting/flash/net/NetStreamPlayTransitions.cpp
  scripting/flash/net/DatagramSocket.cpp
  scripting/flash/printing/flashprinting.cpp
  scripting/flash/profiler/flashprofiler.cpp
  scripting/flash/errors/flasherrors.cpp
  scripting/flash/sampler/flashsampler.cpp
  scripting/flash/security/certificatestatus.cpp
  scripting/flash/sensors/flashsensors.cpp
  scripting/flash/system/flashsystem.cpp
  scripting/flash/system/messagechannel.cpp
  scripting/flash/system/messagechannelstate.cpp
  scripting/flash/system/securitypanel.cpp
  scripting/flash/system/systemupdater.cpp
  scripting/flash/system/systemupdatertype.cpp
  scripting/flash/system/touchscreentype.cpp
  scripting/flash/system/ime.cpp
  scripting/flash/system/jpegloadercontext.cpp
  scripting/flash/text/csmsettings.cpp
  scripting/flash/text/flashtext.cpp
  scripting/flash/text/flashtextengine.cpp
  scripting/flash/text/textrenderer.cpp
  scripting/flash/utils/flashutils.cpp
  scripting/flash/utils/ByteArray.cpp
  scripting/flash/utils/CompressionAlgorithm.cpp
  scripting/flash/utils/Dictionary.cpp
  scripting/flash/utils/Proxy.cpp
  scripting/flash/utils/Timer.cpp
  scripting/flash/utils/IntervalManager.cpp
  scripting/flash/utils/IntervalRunner.cpp
  scripting/flash/ui/Keyboard.cpp
  scripting/flash/ui/Mouse.cpp
  scripting/flash/ui/Multitouch.cpp
  scripting/flash/ui/ContextMenu.cpp
  scripting/flash/ui/ContextMenuItem.cpp
  scripting/flash/ui/ContextMenuBuiltInItems.cpp
  scripting/flash/ui/gameinput.cpp
  scripting/flash/xml/flashxml.cpp
  scripting/toplevel/Array.cpp
  scripting/toplevel/ASQName.cpp
  scripting/toplevel/ASString.cpp
  scripting/toplevel/Boolean.cpp
  scripting/toplevel/Class_base.cpp
  scripting/toplevel/Date.cpp
  scripting/toplevel/Error.cpp
  scripting/toplevel/Global.cpp
  scripting/toplevel/IFunction.cpp
  scripting/toplevel/Integer.cpp
  scripting/toplevel/JSON.cpp
  scripting/toplevel/Math.cpp
  scripting/toplevel/Namespace.cpp
  scripting/toplevel/Null.cpp
  scripting/toplevel/Number.cpp
  scripting/toplevel/RegExp.cpp
  scripting/toplevel/UInteger.cpp
  scripting/toplevel/Undefined.cpp
  scripting/toplevel/Vector.cpp
  scripting/toplevel/XML.cpp
  scripting/toplevel/XMLList.cpp
  scripting/toplevel/AVM1Function.cpp
  scripting/toplevel/toplevel.cpp
  scripting/class.cpp
  scripting/avmplus/avmplus.cpp
  scripting/avm1/avm1key.cpp
  scripting/avm1/avm1sound.cpp
  scripting/avm1/avm1display.cpp
  scripting/avm1/avm1net.cpp
  scripting/avm1/avm1text.cpp
  scripting/avm1/avm1ui.cpp
  scripting/avm1/avm1xml.cpp
  scripting/avm1/avm1media.cpp
  scripting/avm1/avm1array.cpp
  scripting/avm1/avm1date.cpp
  scripting/avm1/avm1filter.cpp
  scripting/avm1/scope.cpp
  scripting/avm1_interpreter.cpp
  platforms/engineutils.cpp
  3rdparty/nanovg/src/nanovg.c
  3rdparty/pugixml/src/pugixml.cpp
  3rdparty/jpegxr/cr_parse.cpp
  3rdparty/jpegxr/cw_emit.cpp
  3rdparty/jpegxr/jpegxr_algo.cpp
  3rdparty/jpegxr/jpegxr_api.cpp
  3rdparty/jpegxr/jpegxr_flags.cpp
  3rdparty/jpegxr/jpegxr_init.cpp
  3rdparty/jpegxr/jpegxr_io.cpp
  3rdparty/jpegxr/jpegxr_pixelformat.cpp
  3rdparty/jpegxr/r_parse.cpp
  3rdparty/jpegxr/r_strip.cpp
  3rdparty/jpegxr/r_tile_frequency.cpp
  3rdparty/jpegxr/r_tile_spatial.cpp
  3rdparty/jpegxr/w_emit.cpp
  3rdparty/jpegxr/w_strip.cpp
  3rdparty/jpegxr/w_tile_frequency.cpp
  3rdparty/jpegxr/w_tile_spatial.cpp
  3rdparty/jpegxr/x_strip.cpp
  3rdparty/avmplus/core/BigInteger.cpp
  3rdparty/avmplus/core/BigInteger.h
  3rdparty/avmplus/core/d2a.cpp
  3rdparty/avmplus/core/d2a.h
  3rdparty/avmplus/pcre/pcre_chartables.cpp
  3rdparty/avmplus/pcre/pcre_compile.cpp
  3rdparty/avmplus/pcre/pcre_config.cpp
  3rdparty/avmplus/pcre/pcre_dfa_exec.cpp
  3rdparty/avmplus/pcre/pcre_exec.cpp
  3rdparty/avmplus/pcre/pcre_fullinfo.cpp
  3rdparty/avmplus/pcre/pcre_get.cpp
  3rdparty/avmplus/pcre/pcre_globals.cpp
  3rdparty/avmplus/pcre/pcre_info.cpp
  3rdparty/avmplus/pcre/pcre_maketables.cpp
  3rdparty/avmplus/pcre/pcre_newline.cpp
  3rdparty/avmplus/pcre/pcre_ord2utf8.cpp
  3rdparty/avmplus/pcre/pcre_refcount.cpp
  3rdparty/avmplus/pcre/pcre_study.cpp
  3rdparty/avmplus/pcre/pcre_tables.cpp
  3rdparty/avmplus/pcre/pcre_try_flipped.cpp
  3rdparty/avmplus/pcre/pcre_valid_utf8.cpp
  3rdparty/avmplus/pcre/pcre_version.cpp
  3rdparty/avmplus/pcre/pcre_xclass.cpp
  3rdparty/avmplus/pcre/config.h
  3rdparty/avmplus/pcre/pcre.h
  3rdparty/avmplus/pcre/pcre_avmplus.h
  3rdparty/avmplus/pcre/pcre_internal.h
  3rdparty/avmplus/pcre/pcreposix.h
  3rdparty/avmplus/pcre/pcre_scanner.h
  3rdparty/imgui/imgui.cpp
  3rdparty/imgui/imgui_draw.cpp
  3rdparty/imgui/imgui_tables.cpp
  3rdparty/imgui/imgui_widgets.cpp
  3rdparty/imgui/backends/imgui_impl_sdl2.cpp
  3rdparty/tinyfiledialogs/tinyfiledialogs.c
  )
SET(LIBNATIVEEXTENSION_SOURCES
  nativeextension/FREimpl.cpp
  )
IF (ENABLE_GLES2 OR ENABLE_GLES3)
SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} 3rdparty/imgui/backends/imgui_impl_opengl3.cpp)
ELSE()
SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} 3rdparty/imgui/backends/imgui_impl_opengl2.cpp)
ENDIF()

IF(MINGW)
    SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/slowpaths_generic.cpp)
ELSEIF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/slowpaths_generic.cpp)
ELSE()
  IF(ENABLE_SSE2)
    IF(${i386})
      SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/fastpaths_x86.cpp)
      SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/fastpaths_i686.asm)
    ELSEIF(${x86_64})
      SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/fastpaths_x86.cpp)
      SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/fastpaths_amd64.asm)
    ELSE()
      SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/slowpaths_generic.cpp)
    ENDIF(${i386})
  ELSE(ENABLE_SSE2)
    SET(LIBSPARK_SOURCES ${LIBSPARK_SOURCES} platforms/slowpaths_generic.cpp)
  ENDIF(ENABLE_SSE2)
ENDIF(MINGW)

# needed for jxr image decoder
SET_SOURCE_FILES_PROPERTIES(${PROJECT_SOURCE_DIR}/src/scripting/flash/display3d/flashdisplay3dtextures.cpp PROPERTIES COMPILE_FLAGS "-D__ANSI__ -DDISABLE_PERF_MEASUREMENT -Wno-endif-labels -I${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/common/include/ -I${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/image/sys/")
SET(CMAKE_C_FLAGS "-D__ANSI__ -DDISABLE_PERF_MEASUREMENT -Wno-endif-labels -I${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/common/include -I${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/image/sys -I${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/common/include")



# liblightspark.so target
IF(EMSCRIPTEN)
  ADD_LIBRARY(spark STATIC ${LIBSPARK_SOURCES})
ELSE()
IF(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  ADD_LIBRARY(spark SHARED ${LIBSPARK_SOURCES})
  #library for handling communication with native extensions, has to be named "libCore.so" on Linux
  ADD_LIBRARY(nativeextension SHARED ${LIBNATIVEEXTENSION_SOURCES})
  SET_TARGET_PROPERTIES(nativeextension PROPERTIES OUTPUT_NAME Core)
  IF(NOT WIN32)
    #win32's cmake doesn't like liblightspark and lightspark.exe having the same name
    SET_TARGET_PROPERTIES(spark PROPERTIES OUTPUT_NAME lightspark)
  ENDIF()
  IF(MINGW)
    #library for handling communication with native extensions, has to be named "Adobe AIR.dll" on Windows
    SET_TARGET_PROPERTIES(nativeextension PROPERTIES PREFIX "")
    SET_TARGET_PROPERTIES(nativeextension PROPERTIES OUTPUT_NAME "Adobe AIR")
    # force linking of "Adobe AIR.dll" dynamically
    TARGET_LINK_LIBRARIES(spark "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/Adobe AIR.dll")
  ELSE()
  TARGET_LINK_LIBRARIES(spark nativeextension)
    SET_TARGET_PROPERTIES(spark PROPERTIES LINK_FLAGS "-Wl,--version-script=${PROJECT_SOURCE_DIR}/src/lightspark.expmap")
  ENDIF()
ELSE(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  IF(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    ADD_LIBRARY(spark SHARED ${LIBSPARK_SOURCES})
    SET_TARGET_PROPERTIES(spark PROPERTIES OUTPUT_NAME lightspark)
	#library for handling communication with native extensions, has to be named "libCore.so"
	ADD_LIBRARY(nativeextension SHARED ${LIBNATIVEEXTENSION_SOURCES})
	SET_TARGET_PROPERTIES(nativeextension PROPERTIES OUTPUT_NAME Core)
	TARGET_LINK_LIBRARIES(spark nativeextension)
  ELSE (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    ADD_LIBRARY(spark STATIC ${LIBSPARK_SOURCES})
	ADD_LIBRARY(nativeextension STATIC ${LIBNATIVEEXTENSION_SOURCES})
	TARGET_LINK_LIBRARIES(spark nativeextension)
  ENDIF (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
ENDIF (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
ENDIF(EMSCRIPTEN)

TARGET_INCLUDE_DIRECTORIES(
	spark
	PUBLIC ${PROJECT_BINARY_DIR}
	PUBLIC ${PROJECT_SOURCE_DIR}/src
	PUBLIC ${PROJECT_SOURCE_DIR}/src/scripting
	PRIVATE ${PROJECT_SOURCE_DIR}/src/3rdparty/jxrlib/jxrgluelib
	PRIVATE ${PROJECT_SOURCE_DIR}/src/3rdparty/avmplus/pcre
	PRIVATE ${PROJECT_SOURCE_DIR}/src/3rdparty/imgui
	PRIVATE ${PROJECT_SOURCE_DIR}/src/3rdparty/imgui/backends
	PUBLIC ${PROJECT_SOURCE_DIR}/src/3rdparty/ordered-map/include
)

TARGET_INCLUDE_DIRECTORIES(
	nativeextension
	PRIVATE "$<TARGET_PROPERTY:spark,INTERFACE_INCLUDE_DIRECTORIES>"
)

SET(LIGHTSPARK_ALL_LIBRARIES ${CAIRO_LIBRARIES} ${ZLIB_LIBRARIES} ${GLIB_LIBRARIES}
	${LLVM_LIBS_CORE} ${LLVM_LIBS_JIT} ${LLVM_LDFLAGS}
	${OPTIONAL_LIBRARIES} ${SDL2_LIBRARIES} ${FREETYPE_LIBRARIES} ${JPEG_LIBRARIES} ${PNG_LIBRARIES}
	${CMAKE_DL_LIBS} ${EXTRA_LIBS_LIBRARIES})
IF(WIN32)
# this is needed so that the resulting binary works on windows7
# see https://github.com/lightspark/lightspark/issues/454
# and https://docs.microsoft.com/en-us/windows/win32/api/usp10/nf-usp10-scriptiscomplex#remarks
# several dependencies include usp10 and gdi32 in the wrong way so we remove all of them first
	LIST(REMOVE_ITEM LIGHTSPARK_ALL_LIBRARIES usp10 gdi32)
# and add them back in the correct order
	SET(LIGHTSPARK_ALL_LIBRARIES ${LIGHTSPARK_ALL_LIBRARIES} usp10 gdi32)
ENDIF(WIN32)
IF(${CMAKE_SYSTEM_PROCESSOR} MATCHES "ppc")
	SET(LIGHTSPARK_ALL_LIBRARIES ${LIGHTSPARK_ALL_LIBRARIES} atomic)
ENDIF()

TARGET_LINK_LIBRARIES(spark ${LIGHTSPARK_ALL_LIBRARIES})
SET_TARGET_PROPERTIES(spark PROPERTIES VERSION "${MAJOR_VERSION}.${MINOR_VERSION}.${PATCH_VERSION}")
SET_TARGET_PROPERTIES(spark PROPERTIES SOVERSION "${MAJOR_VERSION}.${MINOR_VERSION}")

IF(ENABLE_GLES2)
	TARGET_LINK_LIBRARIES(spark ${GLES2_LIBRARIES})
ELSEIF(ENABLE_GLES3)
  TARGET_LINK_LIBRARIES(spark ${GLES3_LIBRARIES})
ELSE()
	TARGET_LINK_LIBRARIES(spark ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES})
ENDIF(ENABLE_GLES2)

PACK_LIBRARY(spark $<TARGET_FILE:spark>)
PACK_LIBRARY(nativeextension $<TARGET_FILE:nativeextension>)
#We have to use LIBRARY on linux and RUNTIME on win32
INSTALL(TARGETS spark RUNTIME_DEPENDENCY_SET spark_dependencies RUNTIME DESTINATION ${PRIVATELIBDIR} LIBRARY DESTINATION ${PRIVATELIBDIR} ARCHIVE DESTINATION ${PRIVATELIBDIR})
INSTALL(TARGETS nativeextension RUNTIME DESTINATION ${PRIVATELIBDIR} LIBRARY DESTINATION ${PRIVATELIBDIR} ARCHIVE DESTINATION ${PRIVATELIBDIR})

# taken from https://github.com/wxFormBuilder/wxFormBuilder/blob/master/src/CMakeLists.txt to add dlls of dependencies to nsis installer
if(WIN32)
  # The installation of runtime dependencies does not take the set paths into account and
  # only searches in system default paths. Therefor paths of libraries not in such locations
  # need to be specified manually. Depending on the used compiler these are different.
  # TODO: Should both variables be used? What do the find_* commands do?
  set(extraDirectories "")
  set(prefixPaths "")
  if(DEFINED ENV{CMAKE_PREFIX_PATH})
    cmake_path(CONVERT "$ENV{CMAKE_PREFIX_PATH}" TO_CMAKE_PATH_LIST pathList NORMALIZE)
    list(APPEND prefixPaths ${pathList})
    unset(pathList)
  endif()
  if(DEFINED CMAKE_PREFIX_PATH)
    cmake_path(CONVERT "${CMAKE_PREFIX_PATH}" TO_CMAKE_PATH_LIST pathList NORMALIZE)
    list(APPEND prefixPaths ${pathList})
    unset(pathList)
  endif()
  # TODO: To find the external libraries, the search path must be augmented for certain libraries
  #       which don't use a standard prefix layout, a certain naming of their directories is assumed.
  #       An alternative would be to install the IMPORTED_RUNTIME_ARTIFACTS of the libraries themself,
  #       but this does not work easily currently because of its limitations
  #       (does not work with UNKNOWN IMPORTED or ALIAS libraries).
  foreach(entry IN LISTS prefixPaths)
    cmake_path(GET entry PARENT_PATH libraryPath)
    cmake_path(GET libraryPath FILENAME libraryName)
    list(APPEND extraDirectories "${entry}/bin")
  endforeach()
  unset(prefixPaths)
  unset(libraryPath)
  unset(libraryName)
  if(MSVC)
    # The compiler runtime libraries are installed in system default paths, because it is expected
    # that the runtime distributables are getting installed along the application, these need to get
    # filtered.
    install(RUNTIME_DEPENDENCY_SET spark_dependencies
      DIRECTORIES
        ${extraDirectories}
      DESTINATION ${BINDIR}
      PRE_EXCLUDE_REGEXES
        [[api-ms-win-.*]]
        [[ext-ms-.*]]
        [[kernel32\.dll]]
        [[msvcp.*\.dll]]
        [[vcruntime.*\.dll]]
      POST_EXCLUDE_REGEXES
        # For some reason some dependencies use forward slashes, some backward slashes
        [[.*[/\]system32/.*\.dll]]
    )
  elseif(MINGW)
    # This environment has its own search paths which are not taken into account and must be specified.
    if(MSYS)
      # The "virtual" paths used by the MSYS environment cannot be used, they must be translated into physical
      # paths of the system.
      find_program(cygpath_cmd NAMES cygpath REQUIRED)
      mark_as_advanced(cygpath_cmd)
      # The mixed mode output equals the CMake path format
      execute_process(COMMAND "${cygpath_cmd}" -m "$ENV{MSYSTEM_PREFIX}/bin" OUTPUT_VARIABLE msysSystemDir OUTPUT_STRIP_TRAILING_WHITESPACE)
      list(APPEND extraDirectories "${msysSystemDir}")
      unset(msysSystemDir)
    else()
      # In plain MinGW environments it is more difficult to determine the paths in a system independent manner.
      # As best effort search the path of the compiler and hope that contains all system libraries.
      find_path(compilerSystemDir NAMES gcc.exe REQUIRED)
      mark_as_advanced(compilerSystemDir)
      list(APPEND extraDirectories "${compilerSystemDir}")
    endif()
    install(RUNTIME_DEPENDENCY_SET spark_dependencies
      DIRECTORIES
        ${extraDirectories}
      DESTINATION ${BINDIR}
      PRE_EXCLUDE_REGEXES
        [[api-ms-win-.*]]
        [[ext-ms-.*]]
        [[kernel32\.dll]]
        [[user32\.dll]]
        [[msvcrt.*\.dll]]
      POST_EXCLUDE_REGEXES
        # For some reason some dependencies use forward slashes, some backward slashes
        [[.*[/\]system32/.*\.dll]]
    )
  endif()
  unset(extraDirectories)
endif()

# lightspark executable target
IF(COMPILE_LIGHTSPARK)
  ADD_EXECUTABLE(lightspark main.cpp)
  TARGET_LINK_LIBRARIES(lightspark spark)

  PACK_EXECUTABLE(lightspark $<TARGET_FILE:lightspark>)
  INSTALL(TARGETS lightspark RUNTIME DESTINATION ${BINDIR})
  IF(UNIX)
    INSTALL(FILES ${PROJECT_SOURCE_DIR}/docs/man/lightspark.1 DESTINATION ${MANUAL_DIRECTORY}/man1/)
  ENDIF(UNIX)
ENDIF(COMPILE_LIGHTSPARK)

# tightspark executable target
IF(COMPILE_TIGHTSPARK)
  ADD_EXECUTABLE(tightspark tightspark.cpp)
  TARGET_LINK_LIBRARIES(tightspark spark nativeextension)
  #With STATICDEPS, all deps are compiled into spark
  IF(NOT STATICDEPS)
    TARGET_LINK_LIBRARIES(tightspark ${GTHREAD_LIBRARIES})
  ENDIF()

  INSTALL(TARGETS tightspark RUNTIME DESTINATION ${BINDIR})
  PACK_EXECUTABLE(tightspark $<TARGET_FILE:tightspark>)
ENDIF(COMPILE_TIGHTSPARK)

# Browser plugins
IF(COMPILE_NPAPI_PLUGIN)
  ADD_SUBDIRECTORY(plugin)
ENDIF(COMPILE_NPAPI_PLUGIN)
IF(COMPILE_PPAPI_PLUGIN)
  ADD_SUBDIRECTORY(plugin_ppapi)
ENDIF(COMPILE_PPAPI_PLUGIN)
