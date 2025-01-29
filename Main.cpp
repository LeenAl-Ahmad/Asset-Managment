#include "Resource.h"
#include "AssetController.h"

int main() {
    AssetController::Instance().Initialize(10000000); // Allocate 10MB

    Resource::Pool = new ObjectPool<Resource>();
    Resource* r1 = Resource::Pool->GetResource();
    r1->AssignNonDefaultValues();

    std::ofstream writeStream("resource.bin", std::ios::out | std::ios::binary);
    r1->Serialize(writeStream);
    writeStream.close();

    std::cout << "*r1 values: ";
    r1->ToString();

    Resource* r2 = Resource::Pool->GetResource();
    std::ifstream readStream("resource.bin", std::ios::in | std::ios::binary);
    r2->Deserialize(readStream);
    readStream.close();

    std::cout << "*r2 values: ";
    r2->ToString();

    delete Resource::Pool;
}
