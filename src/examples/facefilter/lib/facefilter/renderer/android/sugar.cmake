if(ANDROID)
  sugar_files(FACEFILTER_RENDERER_HDRS
    FaceTrackerFactoryJsonAndroid.h
    android_asset_istream.h
    )
  sugar_files(FACEFILTER_RENDERER_SRCS
    FaceTrackerFactoryJsonAndroid.cpp
    android_asset_istream.cpp
    )
endif()