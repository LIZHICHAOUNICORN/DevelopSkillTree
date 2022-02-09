package(default_visibility = ["//visibility:public"])

cc_binary(
    name = "factory_main",
    srcs = [
        "factory_main.cc",
	"IDCardFactory.h",
	"IFactory.h",
	"IDCard.h",
	"IProduct.h",
    ],
    # malloc = "@com_google_tcmalloc//tcmalloc",
    deps = [
        '//third_party/glog:glog',
        '//third_party/gflags:gflags',
    ],
    linkopts = ['-lm', '-lpthread', '-lrt'],
    #linkopts = [ '-lunwind', '-lm', '-lpthread', '-lrt', '-ltcmalloc_and_profiler'],
)
