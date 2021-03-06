#pragma once

#include "filedevice.h"

namespace Iridium
{
    class LocalFileDevice final : public FileDevice
    {
    public:
        Rc<Stream> Open(StringView path, bool read_only) override;
        Rc<Stream> Create(StringView path, bool write_only, bool truncate) override;

        bool Exists(StringView path) override;

        Ptr<FindFileHandle> Find(StringView path) override;

        bool Delete(StringView path) override;

        friend const Rc<LocalFileDevice>& LocalFiles();

    private:
        static StaticRc<LocalFileDevice> s_LocalFiles;
    };

    inline const Rc<LocalFileDevice>& LocalFiles()
    {
        return LocalFileDevice::s_LocalFiles;
    }
} // namespace Iridium
