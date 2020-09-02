#include "byte_stream.hh"

#include <algorithm>
#include <iterator>
#include <stdexcept>

// Dummy implementation of a flow-controlled in-memory byte stream.

// For Lab 0, please replace with a real implementation that passes the
// automated checks run by `make check_lab0`.

// You will need to add private members to the class declaration in `byte_stream.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

ByteStream::ByteStream(const size_t capacity):_buffer(),_capacity(capacity),_size(0),written_size(0),read_size(0),
                                              _input_ended(false){}

size_t ByteStream::write(const string &data) {
    size_t remain_size = remaining_capacity();
    std::string data_buffer = data.substr(0,remain_size);
    for (auto word : data_buffer) {
        _buffer.emplace_back(word);
    }
    written_size += data_buffer.size();
    _size += data_buffer.size();
    return data_buffer.size();
}

//! \param[in] len bytes will be copied from the output side of the buffer
string ByteStream::peek_output(const size_t len) const {
    return std::string(_buffer.begin(),_buffer.begin()+std::min(len,_size));
}

//! \param[in] len bytes will be removed from the output side of the buffer
void ByteStream::pop_output(const size_t len) {
    size_t pop_size = std::min(len,_size);
    for (size_t i = 0; i < pop_size; ++i) {
        _buffer.pop_front();
    }
    read_size += pop_size;
    _size -= pop_size;
}

void ByteStream::end_input() {_input_ended = true;}

bool ByteStream::input_ended() const { return _input_ended; }

size_t ByteStream::buffer_size() const { return _size; }

bool ByteStream::buffer_empty() const { return _size == 0; }

bool ByteStream::eof() const { return input_ended() && buffer_empty(); }

size_t ByteStream::bytes_written() const { return written_size; }

size_t ByteStream::bytes_read() const { return read_size; }

size_t ByteStream::remaining_capacity() const { return _capacity -_size; }
