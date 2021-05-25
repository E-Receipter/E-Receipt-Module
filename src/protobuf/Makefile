main.pb.cc: main.proto
	protoc --cpp_out=. main.proto
test.out: main.pb.cc test.cc
	g++ test.cc main.pb.cc `pkg-config --cflags --libs protobuf` -o test.out
clean:
	rm main.pb.cc