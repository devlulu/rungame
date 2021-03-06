LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/external)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos)
$(call import-add-path,$(LOCAL_PATH)/../../../cocos2d/cocos/audio/include)

LOCAL_MODULE := MyGame_shared

LOCAL_MODULE_FILENAME := libMyGame

LOCAL_SRC_FILES := $(LOCAL_PATH)/hellocpp/main.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/AppDelegate.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/BackgroundLayer.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/MyBodyParser.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/PlayLayer.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/DataManager.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/GameoverScene.cpp
LOCAL_SRC_FILES += $(LOCAL_PATH)/../../../Classes/PlayScene.cpp


LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../Classes
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/AppDelegate.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/BackgroundLayer.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/MyBodyParser.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/PlayLayer.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/DataManager.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/GameoverScene.h
LOCAL_C_INCLUDES += $(LOCAL_PATH)/../../../Classes/PlayScene.h

				

# _COCOS_HEADER_ANDROID_BEGIN
# _COCOS_HEADER_ANDROID_END


LOCAL_STATIC_LIBRARIES := cocos2dx_static

# _COCOS_LIB_ANDROID_BEGIN
# _COCOS_LIB_ANDROID_END

include $(BUILD_SHARED_LIBRARY)

$(call import-module,.)

# _COCOS_LIB_IMPORT_ANDROID_BEGIN
# _COCOS_LIB_IMPORT_ANDROID_END