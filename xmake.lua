add_rules("mode.debug")

set_languages("c++20")

add_repositories("MrowrLib https://github.com/MrowrLib/Packages.git")
add_requires("_Log_", "spdlog", "managed_pointer")

target("void_pointer")
    set_kind("headeronly")
    add_includedirs("include", {public = true})
    add_packages("managed_pointer", { public = true })

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("void_pointer")
    add_packages("_Log_", "spdlog")

target("Example.Deprecated")
    set_kind("binary")
    add_files("Example.Deprecated.cpp")
    add_deps("void_pointer")
    add_packages("_Log_", "spdlog")
