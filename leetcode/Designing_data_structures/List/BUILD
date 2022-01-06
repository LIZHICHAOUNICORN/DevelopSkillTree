package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "linked_list_unit_test",
    srcs = ["linked_list_unit_test.cc",
            "double_linked_list.h"],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
