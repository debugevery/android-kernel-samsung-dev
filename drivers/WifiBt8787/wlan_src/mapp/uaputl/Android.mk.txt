LOCAL_PATH := $(my-dir)
include $(CLEAR_VARS)

LOCAL_MODULE := uaputl.exe
LOCAL_SRC_FILES := uapcmd.c uaputl.c
LOCAL_MODULE_TAGS := eng

include $(BUILD_EXECUTABLE)
