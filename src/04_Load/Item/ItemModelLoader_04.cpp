#include "Item/ItemModelLoader.hpp"

THUMB void ItemModelLoader::Create() {
    gItemModelLoader = new(data_027e0ce0[1], 4) ItemModelLoader();
}

THUMB void ItemModelLoader::Destroy() {
    delete gItemModelLoader;
    gItemModelLoader = NULL;
}
