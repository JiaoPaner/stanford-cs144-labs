//
// Created by jiaopan on 9/3/20.
//

#include "stream_reassembler.hh"

// Dummy implementation of a stream reassembler.

// For Lab 1, please replace with a real implementation that passes the
// automated checks run by `make check_lab1`.

// You will need to add private members to the class declaration in `stream_reassembler.hh`

template <typename... Targs>
void DUMMY_CODE(Targs &&... /* unused */) {}

using namespace std;

StreamReassembler::StreamReassembler(const size_t capacity) : _output(capacity), _capacity(capacity),
                                                              _unassembled_bytes(_capacity),_accepted_bytes(_capacity,false){}

//! \details This function accepts a substring (aka a segment) of bytes,
//! possibly out-of-order, from the logical stream, and assembles any newly
//! contiguous substrings and writes them into the output stream in order.
void StreamReassembler::push_substring(const string &data, const size_t index, const bool eof) {
    if(eof){
        end_index = index + data.size();
        eof_set = true;
    }
    if (_current_index > index + data.size())
        return;
    size_t offset = std::max(index,_current_index) - index;

    for (size_t i = offset; i < data.size(); ++i) {
        if (_accepted_bytes[(i + index) % _capacity] && _unassembled_bytes[(i + index) % _capacity] != data[i])
            break;
        _unassembled_bytes[(i + index) % _capacity] = data[i];
        if (!_accepted_bytes[(i + index) % _capacity]) {
            _accepted_bytes[(i + index) % _capacity] = true;
            _unassembled_bytes_size++;
        }
    }
    assemble_data();
}

size_t StreamReassembler::unassembled_bytes() const { return _unassembled_bytes_size; }

bool StreamReassembler::empty() const {
    return _unassembled_bytes_size == 0;
}

void StreamReassembler::assemble_data() {
    std::string data_to_assemble = "";
    size_t temp_index = _current_index;
    while (_accepted_bytes[temp_index % _capacity]){
        _accepted_bytes[temp_index % _capacity] = false;
        data_to_assemble += _unassembled_bytes[temp_index++ % _capacity];
    }
    size_t nwritten = _output.write(data_to_assemble);
    for (size_t i= nwritten; i < data_to_assemble.size(); i++) {
        _accepted_bytes[(_current_index + i) % _capacity] = true;
    }
    _unassembled_bytes_size -= nwritten;
    _current_index += nwritten;
    if (eof_set && _current_index == end_index) {
        _output.end_input();
    }
}