package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "kmp_unit_test",
    srcs = ["kmp_unit_test.cc",
            "kmp.h",
            "kmp.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "bm_unit_test",
    srcs = ["bm_unit_test.cc",
            "boyer_moore.h",
            "boyer_moore.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "sunday_unit_test",
    srcs = ["sunday_unit_test.cc",
            "sunday.h",
            "sunday.cc"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
cc_binary(
    name = "aho_corasick_unit_test",
    srcs = ["aho_corasick_unit_test.cc",
            "aho_corasick.cc", 
            "aho_corasick.h"], 
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
