package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "singleton",
    srcs = ["singleton.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "singleton_main",
    srcs = [
        "singleton_main.cc",
        "singleton_template.h"
    ],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        "@com_github_google_glog//:glog",
        "@com_github_gflags_gflags//:gflags",
    ],
    linkopts = ['-lm', '-lpthread'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
