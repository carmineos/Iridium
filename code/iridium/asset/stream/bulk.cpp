#include "bulk.h"

namespace Iridium
{
    BulkStream::BulkStream(Rc<Stream> handle)
        : input_(handle)
    {}

    StreamPosition BulkStream::Seek(i64 offset, SeekWhence whence)
    {
        switch (whence)
        {
            case SeekWhence::Set: here_ = offset; break;
            case SeekWhence::Cur: here_ += offset; break;
            case SeekWhence::End: here_ = input_->Size() + offset; break;
        }

        return here_;
    }

    StreamPosition BulkStream::Tell()
    {
        return here_;
    }

    StreamPosition BulkStream::Size()
    {
        return input_->Size();
    }

    usize BulkStream::Read(void* ptr, usize len)
    {
        if (!here_.valid())
            return 0;

        usize result = input_->ReadBulk(ptr, len, here_.get());

        here_ += result;

        return result;
    }

    usize BulkStream::ReadBulk(void* ptr, usize len, u64 offset)
    {
        return input_->ReadBulk(ptr, len, offset);
    }

    bool BulkStream::IsBulkSync() const
    {
        return input_->IsBulkSync();
    }

    Rc<Stream> BulkStream::GetBulkStream(u64&, u64)
    {
        return input_;
    }
} // namespace Iridium
