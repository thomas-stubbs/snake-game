load("@rules_cc//cc:defs.bzl", "cc_binary", "cc_library")

cc_library(
    name = "snake",
    srcs = ["snake.cc"],
    hdrs = ["snake.h"],
    deps = ["//lib:API"],
    visibility = ["//main:__pkg__", "//test:__pkg__"],
)

cc_binary(
    name = "game",
    srcs = ["game.cc"],
    deps = [
        ":snake",
        "//lib:API",
    ],
)
