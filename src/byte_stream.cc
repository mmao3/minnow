#include "byte_stream.hh"

using namespace std;

ByteStream::ByteStream(uint64_t capacity) : capacity_(capacity), buffer_(), total_pushed_(0), total_popped_(0) {}

void Writer::push(string data)
{
  uint64_t writable = min(data.size(), capacity_ - buffer_.size());
  for (size_t i = 0; i < writable; i++) {
    buffer_.push_back(data[i]);
  }
  total_pushed_ += writable;
}

void Writer::close()
{
  closed_ = true;
}

bool Writer::is_closed() const
{
  return closed_;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buffer_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return total_pushed_;
}

string_view Reader::peek() const
{
  if (buffer_.empty()) {
    return std::string_view();  // Return an empty string_view if buffer is empty
  }
  return std::string_view(&buffer_.front(), buffer_.size());

}

void Reader::pop(uint64_t len)
{
  uint64_t to_pop = min(len, buffer_.size());
  if (to_pop == buffer_.size()) {
        buffer_.clear();  // Removes all elements in the buffer
    } else {
        // Pop elements one by one when len is less than buffer size
        for (size_t i = 0; i < to_pop; i++) {
            buffer_.pop_front();
        }
    }

  total_popped_ += to_pop;
}

bool Reader::is_finished() const
{
  return closed_ && buffer_.empty();
}

uint64_t Reader::bytes_buffered() const
{
  return buffer_.size();
}

uint64_t Reader::bytes_popped() const
{
  return total_popped_;
}
