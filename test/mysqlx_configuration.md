c_cpp_properties.json

    {
        "configurations": [
            {
                "name": "Mac",
                "includePath": [
                    "${workspaceFolder}/**",
                    "/usr/local/mysql-connector-c++-8.0.21/include"
                ],
                "defines": [],
                "macFrameworkPath": [],
                "compilerPath": "/usr/bin/g++",
                "cStandard": "c11",
                "cppStandard": "c++11",
                "intelliSenseMode": "clang-x64",
                "browse": {
                    "path": [
                        "/usr/local/mysql-connector-c++-8.0.21"
                    ],
                    "limitSymbolsToIncludedHeaders": true,
                    "databaseFilename": ""
                }
            }
        ],
        "version": 4
    }
    
launch.json
    
    {
        // Use IntelliSense to learn about possible attributes.
        // Hover to view descriptions of existing attributes.
        // For more information, visit: https://go.microsoft.com/fwlink/?linkid=830387
        "version": "0.2.0",
        "configurations": [
        
            {
                "name": "g++ - 生成和调试活动文件",
                "type": "cppdbg",
                "request": "launch",
                "program": "${fileDirname}/${fileBasenameNoExtension}",
                "args": [],
                "stopAtEntry": false,
                "cwd": "${workspaceFolder}",
                "environment": [],
                "externalConsole": false,
                "MIMode": "lldb",
                "miDebuggerPath": "/usr/bin/g++",
                "preLaunchTask": "C/C++: g++ build active file"
            }
        ]
    }
    
tasks.json

    {
        "version": "2.0.0",
        "tasks": [
            {
                "type": "shell",
                "label": "C/C++: g++ build active file",
                "command": "/usr/bin/g++",
                "args": [
                    "-std=c++17",
                    "-stdlib=libc++",
                    "-g",
                    "${file}",
                    "-o",
                    "${fileDirname}/${fileBasenameNoExtension}",
                    "-I",
                    "/usr/local/mysql-connector-c++-8.0.21/include",
                    "-L",
                    "/usr/local/mysql-connector-c++-8.0.21/lib64",
                    "-l",
                    "mysqlcppconn8",
                ],
                "options": {
                    "cwd": "${workspaceFolder}"
                },
                "problemMatcher": [
                    "$gcc"
                ],
                "group": {
                    "kind": "build",
                    "isDefault": true
                }
            }
        ]
    }
