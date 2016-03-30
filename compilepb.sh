#!/bin/sh
protoc -I=./pbs --cpp_out=./pbs_compiled ./pbs/*.proto
