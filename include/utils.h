enum class StorageUnit { MiB, GiB };

inline double convertTo(unsigned long long size, StorageUnit targetUnit) {
    switch (targetUnit) {
        case StorageUnit::MiB:
            return size / 1024.0;
        case StorageUnit::GiB:
            return size / (1024.0 * 1024.0);
    }
    return 0.0;
}
