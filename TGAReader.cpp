#include "TGAReader.h"

#include "AssetController.h"

TGAReader::TGAReader() {
    m_header = { };
    m_data = nullptr;
}

void TGAReader::ProcessAsset(Asset* _rawTGA, ImageInfo* _imageInfo) {
    memcpy(&m_header, _rawTGA->GetData(), sizeof(TGAHeader));

    // Check if format is supported
    M_ASSERT(m_header.DataTypeCode == 2, "Can only handle image type 2");
    M_ASSERT(m_header.BitsPerPixel == 24 || m_header.BitsPerPixel == 32,
        "Can only handle pixel depths of 24, and 32");
    M_ASSERT(m_header.ColourMapType == 0, "Can only handle colour map types of 0");

    // Calculate data offset in asset buffer
    int dataOffset = sizeof(TGAHeader);
    dataOffset += m_header.IDLength;
    dataOffset += m_header.ColourMapType * m_header.ColourMapLength;

    _imageInfo->Width = m_header.Width;
    _imageInfo->Height = m_header.Height;
    _imageInfo->BitsPerPixel = m_header.BitsPerPixel;
    _imageInfo->DataOffset = dataOffset;
}

Asset* TGAReader::LoadTGAFromFile(string _file, ImageInfo* _imageInfo) {
    // Read the file into an asset
    m_data = AssetController::Instance().GetAsset(_file);
    ProcessAsset(m_data, _imageInfo);
    return m_data;
}

bool TGAReader::SaveTGAToFile(const std::string& fileName, const byte* imageData, short width, short height, char bitsPerPixel) {
    if (!imageData) {
        std::cerr << "Error: Image data is null, cannot save TGA file.\n";
        return false;
    }

    // Validate pixel depth
    if (bitsPerPixel != 24 && bitsPerPixel != 32) {
        std::cerr << "Error: Only 24-bit and 32-bit images are supported.\n";
        return false;
    }

    // Initialize TGA header
    TGAHeader header = {};
    header.DataTypeCode = 2;  // Uncompressed RGB
    header.Width = width;
    header.Height = height;
    header.BitsPerPixel = bitsPerPixel;
    header.ImageDescriptor = (bitsPerPixel == 32) ? 8 : 0; // Alpha channel for 32-bit

    // Open output file
    std::ofstream outFile(fileName, std::ios::binary);
    if (!outFile) {
        std::cerr << "Error: Could not open file for writing: " << fileName << "\n";
        return false;
    }

    // Write header and image data
    outFile.write(reinterpret_cast<const char*>(&header), sizeof(TGAHeader));
    outFile.write(reinterpret_cast<const char*>(imageData), width * height * (bitsPerPixel / 8));
    outFile.close();

    std::cout << "TGA file saved successfully: " << fileName << "\n";
    return true;
}



