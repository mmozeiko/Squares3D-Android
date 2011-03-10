LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := expat
LOCAL_CFLAGS    := -DHAVE_MEMMOVE
LOCAL_C_INCLUDES := $(LOCAL_PATH)/expat
LOCAL_ARM_MODE  := arm
LOCAL_SRC_FILES := expat/xmlparse.c expat/xmlrole.c expat/xmltok.c

include $(BUILD_STATIC_LIBRARY)



include $(CLEAR_VARS)

LOCAL_MODULE     := tremolo
LOCAL_ARM_MODE   := arm
LOCAL_SRC_FILES  := tremolo/bitwise.c      \
                    tremolo/bitwiseARM.S   \
                    tremolo/codebook.c     \
                    tremolo/dpen.S         \
                    tremolo/dsp.c          \
                    tremolo/floor0.c       \
                    tremolo/floor1.c       \
                    tremolo/floor1ARM.S    \
                    tremolo/floor1LARM.S   \
                    tremolo/floor_lookup.c \
                    tremolo/framing.c      \
                    tremolo/info.c         \
                    tremolo/mapping0.c     \
                    tremolo/mdct.c         \
                    tremolo/mdctARM.S      \
                    tremolo/mdctLARM.S     \
                    tremolo/misc.c         \
                    tremolo/res012.c       \
                    tremolo/speed.S        \
                    tremolo/vorbisfile.c

LOCAL_CFLAGS    := -ffast-math -freciprocal-math -funsafe-math-optimizations -fsingle-precision-constant -D_ARM_ASSEM_

include $(BUILD_STATIC_LIBRARY)



include $(CLEAR_VARS)

LOCAL_MODULE    := newton

LOCAL_CFLAGS    := -ffast-math -freciprocal-math -funsafe-math-optimizations -fsingle-precision-constant -D_LINUX_VER -D_LINUX_VER_64 -D_SCALAR_ARITHMETIC_ONLY

LOCAL_C_INCLUDES := $(LOCAL_PATH)/newton/coreLibrary_200/source/core \
                    $(LOCAL_PATH)/newton/coreLibrary_200/source/physics \
                    $(LOCAL_PATH)/newton/coreLibrary_200/source/newton

LOCAL_ARM_MODE  := arm

LOCAL_SRC_FILES := newton/coreLibrary_200/source/core/dg.cpp \
                   newton/coreLibrary_200/source/core/dgRef.cpp \
                   newton/coreLibrary_200/source/core/dgCRC.cpp \
                   newton/coreLibrary_200/source/core/dgTree.cpp \
                   newton/coreLibrary_200/source/core/dgNode.cpp \
                   newton/coreLibrary_200/source/core/dgTypes.cpp \
                   newton/coreLibrary_200/source/core/dgMatrix.cpp \
                   newton/coreLibrary_200/source/core/dgGoogol.cpp \
                   newton/coreLibrary_200/source/core/dgMemory.cpp \
                   newton/coreLibrary_200/source/core/dgSphere.cpp \
                   newton/coreLibrary_200/source/core/dgRandom.cpp \
                   newton/coreLibrary_200/source/core/dgThreads.cpp \
                   newton/coreLibrary_200/source/core/dgPolyhedra.cpp \
                   newton/coreLibrary_200/source/core/dgQuaternion.cpp \
                   newton/coreLibrary_200/source/core/dgConvexHull3d.cpp \
                   newton/coreLibrary_200/source/core/dgConvexHull4d.cpp \
                   newton/coreLibrary_200/source/core/dgIntersections.cpp \
                   newton/coreLibrary_200/source/core/dgAABBPolygonSoup.cpp \
                   newton/coreLibrary_200/source/core/dgSmallDeterminant.cpp \
                   newton/coreLibrary_200/source/core/dgPolygonSoupBuilder.cpp \
                   newton/coreLibrary_200/source/core/dgPolyhedraMassProperties.cpp \
                   newton/coreLibrary_200/source/core/dgDelaunayTetrahedralization.cpp \
                   newton/coreLibrary_200/source/physics/dgWorld.cpp \
                   newton/coreLibrary_200/source/physics/dgBody.cpp \
                   newton/coreLibrary_200/source/physics/dgMeshEffect.cpp \
                   newton/coreLibrary_200/source/physics/dgMeshEffect2.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionConvex.cpp \
                   newton/coreLibrary_200/source/physics/dgBallConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgBilateralConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCorkscrewConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgHingeConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgNarrowPhaseCollision.cpp \
                   newton/coreLibrary_200/source/physics/dgBroadPhaseCollision.cpp \
                   newton/coreLibrary_200/source/physics/dgMinkowskiConv.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionBox.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionCapsule.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionBVH.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionMesh.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionUserMesh.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionChamferCylinder.cpp \
                   newton/coreLibrary_200/source/physics/dgPointToCurveConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionCone.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionConvexHull.cpp \
                   newton/coreLibrary_200/source/physics/dgSlidingConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionConvexModifier.cpp \
                   newton/coreLibrary_200/source/physics/dgUniversalConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCollision.cpp \
                   newton/coreLibrary_200/source/physics/dgUpVectorConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionCylinder.cpp \
                   newton/coreLibrary_200/source/physics/dgUserConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionEllipse.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionNull.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionScene.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionCompoundBreakable.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionHeightField.cpp \
                   newton/coreLibrary_200/source/physics/dgWorldDynamicUpdate.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionSphere.cpp \
                   newton/coreLibrary_200/source/physics/dgCollisionCompound.cpp \
                   newton/coreLibrary_200/source/physics/dgConnectorConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgConstraint.cpp \
                   newton/coreLibrary_200/source/physics/dgBodyMasterList.cpp \
                   newton/coreLibrary_200/source/physics/dgContact.cpp \
                   newton/coreLibrary_200/source/newton/Newton.cpp \
                   newton/coreLibrary_200/source/newton/NewtonClass.cpp

include $(BUILD_STATIC_LIBRARY)


include $(CLEAR_VARS)

LOCAL_MODULE     := openal-soft
LOCAL_ARM_MODE   := arm
LOCAL_C_INCLUDES := $(LOCAL_PATH)/openal-soft/include $(LOCAL_PATH)/openal-soft/OpenAL32/Include
LOCAL_SRC_FILES  := openal-soft/OpenAL32/alAuxEffectSlot.c \
                    openal-soft/OpenAL32/alBuffer.c        \
                    openal-soft/OpenAL32/alDatabuffer.c    \
                    openal-soft/OpenAL32/alEffect.c        \
                    openal-soft/OpenAL32/alError.c         \
                    openal-soft/OpenAL32/alExtension.c     \
                    openal-soft/OpenAL32/alFilter.c        \
                    openal-soft/OpenAL32/alListener.c      \
                    openal-soft/OpenAL32/alSource.c        \
                    openal-soft/OpenAL32/alState.c         \
                    openal-soft/OpenAL32/alThunk.c         \
                    openal-soft/Alc/ALc.c                  \
                    openal-soft/Alc/alcConfig.c            \
                    openal-soft/Alc/alcEcho.c              \
                    openal-soft/Alc/alcModulator.c         \
                    openal-soft/Alc/alcReverb.c            \
                    openal-soft/Alc/alcRing.c              \
                    openal-soft/Alc/alcThread.c            \
                    openal-soft/Alc/ALu.c                  \
                    openal-soft/Alc/android.c              \
                    openal-soft/Alc/bs2b.c                 \
                    openal-soft/Alc/null.c                 \

LOCAL_CFLAGS     := -DAL_BUILD_LIBRARY -DAL_ALEXT_PROTOTYPES
LOCAL_LDLIBS     := -llog -Wl,-s

include $(BUILD_SHARED_LIBRARY)




include $(CLEAR_VARS)

LOCAL_MODULE    := Squares3D
LOCAL_SRC_FILES := glue.cpp \
                   source/audio.cpp \
                   source/ball.cpp \
                   source/body.cpp \
                   source/camera.cpp \
                   source/collision.cpp \
                   source/config.cpp \
                   source/fence.cpp \
                   source/file.cpp \
                   source/font.cpp \
                   source/formatter.cpp \
                   source/fps.cpp \
                   source/game.cpp \
                   source/geometry.cpp \
                   source/grass.cpp \
                   source/input.cpp \
                   source/input_button.cpp \
                   source/input_mover.cpp \
                   source/intro.cpp \
                   source/language.cpp \
                   source/level.cpp \
                   source/material.cpp \
                   source/menu.cpp \
                   source/menu_entries.cpp \
                   source/menu_languages.cpp \
                   source/menu_submenu.cpp \
                   source/mesh.cpp \
                   source/message.cpp \
                   source/messages.cpp \
                   source/music.cpp \
                   source/network.cpp \
                   source/oggDecoder.cpp \
                   source/player.cpp \
                   source/player_ai.cpp \
                   source/player_local.cpp \
                   source/profile.cpp \
                   source/properties.cpp \
                   source/property.cpp \
                   source/random.cpp \
                   source/referee_base.cpp \
                   source/referee_local.cpp \
                   source/scoreboard.cpp \
                   source/skybox.cpp \
                   source/sound.cpp \
                   source/sound_buffer.cpp \
                   source/texture.cpp \
                   source/timer.cpp \
                   source/utilities.cpp \
                   source/video.cpp \
                   source/vmath.cpp \
                   source/world.cpp \
                   source/xml.cpp

LOCAL_CFLAGS   := -ffast-math -freciprocal-math -funsafe-math-optimizations -fsingle-precision-constant
#-ffloat-store

LOCAL_C_INCLUDES := $(LOCAL_PATH)/newton \
                    $(LOCAL_PATH)/tremolo \
                    $(LOCAL_PATH)/expat \
                    $(LOCAL_PATH)/openal-soft/include

LOCAL_ARM_MODE  := arm
LOCAL_LDLIBS    := -llog -lz -lGLESv1_CM
LOCAL_STATIC_LIBRARIES := newton tremolo expat
LOCAL_SHARED_LIBRARIES := openal-soft

include $(BUILD_SHARED_LIBRARY)
