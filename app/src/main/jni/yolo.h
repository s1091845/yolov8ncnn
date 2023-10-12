// Tencent is pleased to support the open source community by making ncnn available.
//
// Copyright (C) 2021 THL A29 Limited, a Tencent company. All rights reserved.
//
// Licensed under the BSD 3-Clause License (the "License"); you may not use this file except
// in compliance with the License. You may obtain a copy of the License at
//
// https://opensource.org/licenses/BSD-3-Clause
//
// Unless required by applicable law or agreed to in writing, software distributed
// under the License is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
// CONDITIONS OF ANY KIND, either express or implied. See the License for the
// specific language governing permissions and limitations under the License.

#ifndef YOLO_H
#define YOLO_H

#include <opencv2/core/core.hpp>

#include <net.h>
#include <jni.h>

struct Object
{
    cv::Rect_<float> rect;
    int label;
    float prob;
};
struct GridAndStride
{
    int grid0;
    int grid1;
    int stride;
};
class Yolo
{
public:
    Yolo();

    int load(const char* modeltype, int target_size, const float* mean_vals, const float* norm_vals, bool use_gpu = false);

    int load(AAssetManager* mgr, const char* modeltype, int target_size, const float* mean_vals, const float* norm_vals, bool use_gpu = false);

    int detect(const cv::Mat& rgb, std::vector<Object>& objects, float prob_threshold = 0.4f, float nms_threshold = 0.5f);

    // 在 Yolo 类中存储 JNIEnv 和 MainActivity 对象引用
//    JNIEXPORT void JNICALL Java_com_tencent_yolov8ncnn_MainActivity_receiveClassName(JNIEnv* env, jobject mainActivityObj) {
//        javaEnv = env;
//        mainActivityObject = mainActivityObj;
//    }

    int draw(cv::Mat& rgb, const std::vector<Object>& objects);

private:
    ncnn::Net yolo;
    int target_size;
    float mean_vals[3];
    float norm_vals[3];
    ncnn::UnlockedPoolAllocator blob_pool_allocator;
    ncnn::PoolAllocator workspace_pool_allocator;
//    const char* current_class_name; // 私有成员变量用于存储类名
//    JNIEnv* javaEnv; // 存储 JNIEnv
//    jobject mainActivityObject; // 存储 MainActivity 对象引用
//    jmethodID receiveClassNameMethod; // 存储 receiveClassName 方法的 ID
};

#endif // NANODET_H
