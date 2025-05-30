// original code from http://code.google.com/p/puyotools/ (BSD License) written by not.nmn and nickwor
// ported to C by Luigi Auriemma

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//typedef unsigned short  ushort;
//typedef unsigned int    uint;
//typedef unsigned char   byte;



// the compressed data must start from offset 0x10!
//                uint compressedSize   = data.ReadUInt(0x8).SwapEndian() + 16; // Compressed Size
//                uint decompressedSize = data.ReadUInt(0xC).SwapEndian();      // Decompressed Size
//                uint Cpointer = 0x10; // Compressed Pointer
int puyo_cnx_unpack(byte *compressedData, int compressedSize, byte *decompressedData, int decompressedSize) {
    int     i,
            j;

                uint Cpointer = 0x0;  // Compressed Pointer // was 0x10
                uint Dpointer = 0x0;  // Decompressed Pointer
                while (Cpointer < compressedSize && Dpointer < decompressedSize)
                {
                    byte Cflag = compressedData[Cpointer];
                    Cpointer++;

                    for (i = 0; i < 4; i++)
                    {
                        /* Check for the mode */
                        switch ((Cflag >> (i * 2)) & 3)
                        {
                            /* Padding Mode
					         * All CNX archives seem to be packed in 0x800 chunks. when nearing
					         * a 0x800 cutoff, there usually is a padding command at the end to skip
					         * a few bytes (to the next 0x800 chunk, i.e. 0x4800, 0x7000, etc.) */
                            case 0: {
                                byte temp_byte = compressedData[Cpointer];
                                Cpointer      += (uint)(temp_byte & 0xFF) + 1;

                                i = 3;
                                break;
                            }
                            /* Single Byte Copy Mode */
                            case 1: {
                                decompressedData[Dpointer] = compressedData[Cpointer];
                                Cpointer++;
                                Dpointer++;
                                break;
                            }
                            /* Copy from destination buffer to current position */
                            case 2: {
                                //uint temp_word = BitConverter.ToUInt16(compressedData, (int)Cpointer).SwapEndian();
                                uint temp_word = (compressedData[Cpointer] << 8) | compressedData[Cpointer+1];

                                uint off = (temp_word >> 5)   + 1;
                                uint len = (temp_word & 0x1F) + 4;

                                Cpointer += 2;

                                for (j = 0; j < len; j++)
                                {
                                    decompressedData[Dpointer] = decompressedData[Dpointer - off];
                                    Dpointer++;
                                }

                                break;
                            }
                            /* Direct Block Copy (first byte signifies length of copy) */
                            case 3: {
                                byte blockLength = compressedData[Cpointer];
                                Cpointer++;

                                for (j = 0; j < blockLength; j++)
                                {
                                    decompressedData[Dpointer] = compressedData[Cpointer];
                                    Cpointer++;
                                    Dpointer++;
                                }

                                break;
                            }
                        }
                    }
                }
    return(Dpointer);
}



// the compressed data must start from offset 0x8!
//                uint CompressedSize   = (uint)data.Length;
//                uint DecompressedSize = data.ReadUInt(0x4) >> 8;
//                uint SourcePointer = 0x8;
int puyo_cxlz_unpack(byte *CompressedData, int CompressedSize, byte *DecompressedData, int DecompressedSize) {
    int     i,
            j;
                uint SourcePointer = 0x0;   // was 0x8
                uint DestPointer   = 0x0;

                // Start Decompression
                while (SourcePointer < CompressedSize && DestPointer < DecompressedSize)
                {
                    byte Flag = CompressedData[SourcePointer]; // Compression Flag
                    SourcePointer++;

                    for (i = 7; i >= 0; i--)
                    {
                        if ((Flag & (1 << i)) == 0) // Data is not compressed
                        {
                            DecompressedData[DestPointer] = CompressedData[SourcePointer];
                            SourcePointer++;
                            DestPointer++;
                        }
                        else // Data is compressed
                        {
                            int Distance = (((CompressedData[SourcePointer] & 0xF) << 8) | CompressedData[SourcePointer + 1]) + 1;
                            int Amount   = (CompressedData[SourcePointer] >> 4) + 3;
                            SourcePointer += 2;

                            // Copy the data
                            for (j = 0; j < Amount; j++)
                                DecompressedData[DestPointer + j] = DecompressedData[DestPointer - Distance + j];
                            DestPointer += (uint)Amount;
                        }

                        // Check for out of range
                        if (SourcePointer >= CompressedSize || DestPointer >= DecompressedSize)
                            break;
                    }
                }
    return(DestPointer);
}



        uint GetNewMagicValue(uint xValue)
        {
            uint x;

            x = (((((((xValue << 1) + xValue) << 5) - xValue) << 5) + xValue) << 7) - xValue;
            x = (x << 6) - x;
            x = (x << 4) - x;

            return ((x << 2) - x) + 12345;
        }
        byte DecryptByte(byte value, uint xValue)
        {
            uint t0 = ((uint)xValue >> 16) & 0x7fff;
            return (byte)(value ^ ((uint)(((t0 << 8) - t0) >> 15)));
        }
// the compressed data must start from offset 0x34!
//                uint CompressedSize   = data.ReadUInt(0x4);
//                uint DecompressedSize = data.ReadUInt(0x30);
//                uint MagicValue       = data.ReadUInt(0x34);
//                uint SourcePointer = 0x40;
int puyo_lz00_unpack(byte *CompressedData, int CompressedSize, byte *DecompressedData, int DecompressedSize) {
    int     i,
            j;
                byte *DestBuffer = calloc(0x1000, 1);

                uint MagicValue    = *(uint *)CompressedData;
                uint SourcePointer = 0x40-0x34;   // was 0x40;
                uint DestPointer   = 0x0;
                uint BufferPointer = 0xFEE;

                // Start Decompression
                while (SourcePointer < CompressedSize && DestPointer < DecompressedSize)
                {
                    MagicValue = GetNewMagicValue(MagicValue);
                    byte Flag = DecryptByte(CompressedData[SourcePointer], MagicValue); // Compression Flag
                    SourcePointer++;

                    for (i = 0; i < 8; i++)
                    {
                        if ((Flag & (1 << i)) > 0) // Data is not compressed
                        {
                            MagicValue = GetNewMagicValue(MagicValue);
                            DecompressedData[DestPointer] = DecryptByte(CompressedData[SourcePointer], MagicValue);
                            DestBuffer[BufferPointer]     = DecompressedData[DestPointer];
                            SourcePointer++;
                            DestPointer++;
                            BufferPointer = (BufferPointer + 1) & 0xFFF;
                        }
                        else // Data is compressed
                        {
                            MagicValue      = GetNewMagicValue(MagicValue);
                            byte PairFirst  = DecryptByte(CompressedData[SourcePointer], MagicValue);
                            MagicValue      = GetNewMagicValue(MagicValue);
                            byte PairSecond = DecryptByte(CompressedData[SourcePointer + 1], MagicValue);

                            int Offset = ((((PairSecond >> 4) & 0xF) << 8) | PairFirst);
                            int Amount = (PairSecond & 0xF) + 3;
                            SourcePointer += 2;

                            for (j = 0; j < Amount; j++)
                            {
                                DecompressedData[DestPointer + j] = DestBuffer[(Offset + j) & 0xFFF];
                                DestBuffer[BufferPointer]         = DecompressedData[DestPointer + j];
                                BufferPointer = (BufferPointer + 1) & 0xFFF;
                            }
                            DestPointer += (uint)Amount;
                        }

                        // Check for out of range
                        if (SourcePointer >= CompressedSize || DestPointer >= DecompressedSize)
                            break;
                    }
                }
    free(DestBuffer);
    return(DestPointer);
}



// the compressed data must start from offset 0x10!
//                uint CompressedSize   = data.ReadUInt(0x4);
//                uint DecompressedSize = data.ReadUInt(0x8);
//                uint SourcePointer = 0x10;
int puyo_lz01_unpack(byte *CompressedData, int CompressedSize, byte *DecompressedData, int DecompressedSize) {
    int     i,
            j;
                byte *DestBuffer = calloc(0x1000, 1);

                uint SourcePointer = 0x0; // was 0x10;
                uint DestPointer   = 0x0;
                uint BufferPointer = 0xFEE;

                // Start Decompression
                while (SourcePointer < CompressedSize && DestPointer < DecompressedSize)
                {
                    byte Flag = CompressedData[SourcePointer]; // Compression Flag
                    SourcePointer++;

                    for (i = 0; i < 8; i++)
                    {
                        if ((Flag & (1 << i)) > 0) // Data is not compressed
                        {
                            DecompressedData[DestPointer] = CompressedData[SourcePointer];
                            DestBuffer[BufferPointer]     = DecompressedData[DestPointer];
                            SourcePointer++;
                            DestPointer++;
                            BufferPointer = (BufferPointer + 1) & 0xFFF;
                        }
                        else // Data is compressed
                        {
                            int Offset = ((((CompressedData[SourcePointer + 1] >> 4) & 0xF) << 8) | CompressedData[SourcePointer]);
                            int Amount = (CompressedData[SourcePointer + 1] & 0xF) + 3;
                            SourcePointer += 2;

                            for (j = 0; j < Amount; j++)
                            {
                                DecompressedData[DestPointer + j] = DestBuffer[(Offset + j) & 0xFFF];
                                DestBuffer[BufferPointer]         = DecompressedData[DestPointer + j];
                                BufferPointer = (BufferPointer + 1) & 0xFFF;
                            }
                            DestPointer += (uint)Amount;
                        }

                        // Check for out of range
                        if (SourcePointer >= CompressedSize || DestPointer >= DecompressedSize)
                            break;
                    }
                }
    free(DestBuffer);
    return(DestPointer);
}



// the compressed data must start from offset 0x4!
//                uint CompressedSize   = (uint)data.Length;
//                uint DecompressedSize = data.ReadUInt(0x0) >> 8;
//                uint SourcePointer = 0x4;
int puyo_lzss_unpack(byte *CompressedData, int CompressedSize, byte *DecompressedData, int DecompressedSize) {
    int     i,
            j;
                uint SourcePointer = 0x0; // was 0x4;
                uint DestPointer   = 0x0;

                // Start Decompression
                while (SourcePointer < CompressedSize && DestPointer < DecompressedSize)
                {
                    byte Flag = CompressedData[SourcePointer]; // Compression Flag
                    SourcePointer++;

                    for (i = 7; i >= 0; i--)
                    {
                        if ((Flag & (1 << i)) == 0) // Data is not compressed
                        {
                            DecompressedData[DestPointer] = CompressedData[SourcePointer];
                            SourcePointer++;
                            DestPointer++;
                        }
                        else // Data is compressed
                        {
                            int Distance = (((CompressedData[SourcePointer] & 0xF) << 8) | CompressedData[SourcePointer + 1]) + 1;
                            int Amount   = (CompressedData[SourcePointer] >> 4) + 3;
                            SourcePointer += 2;

                            // Copy the data
                            for (j = 0; j < Amount; j++)
                                DecompressedData[DestPointer + j] = DecompressedData[DestPointer - Distance + j];
                            DestPointer += (uint)Amount;
                        }

                        // Check for out of range
                        if (SourcePointer >= CompressedSize || DestPointer >= DecompressedSize)
                            break;
                    }
                }
    return(DestPointer);
}



// the compressed data must start from offset 0x4!
//                uint CompressedSize   = (uint)data.Length;
//                uint DecompressedSize = data.ReadUInt(0x0) >> 8;
//                uint SourcePointer = 0x4;
int puyo_onz_unpack(byte *CompressedData, int CompressedSize, byte *DecompressedData, int DecompressedSize) {
    int     i,
            j;
                uint SourcePointer = 0x0; // was 0x4;
                uint DestPointer   = 0x0;

                // not handled here because this is a memory2memory decompression
                //if (DecompressedSize == 0) // Next 4 bytes are the decompressed size
                //{
                    //DecompressedSize = data.ReadUInt(0x4);
                    //SourcePointer += 0x4;
                //}

                // Start Decompression
                while (SourcePointer < CompressedSize && DestPointer < DecompressedSize)
                {
                    byte Flag = CompressedData[SourcePointer]; // Compression Flag
                    SourcePointer++;

                    for (i = 7; i >= 0; i--)
                    {
                        if ((Flag & (1 << i)) == 0) // Data is not compressed
                        {
                            DecompressedData[DestPointer] = CompressedData[SourcePointer];
                            SourcePointer++;
                            DestPointer++;
                        }
                        else // Data is compressed
                        {
                            int Distance;
                            int Amount;

                            // Let's determine how many bytes the distance & length pair take up
                            switch (CompressedData[SourcePointer] >> 4)
                            {
                                case 0: { // 3 bytes
                                    Distance = (((CompressedData[SourcePointer + 1] & 0xF) << 8) | CompressedData[SourcePointer + 2]) + 1;
                                    Amount   = (((CompressedData[SourcePointer] & 0xF) << 4) | (CompressedData[SourcePointer + 1] >> 4)) + 17;
                                    SourcePointer += 3;
                                    break;
                                }
                                case 1: { // 4 bytes
                                    Distance = (((CompressedData[SourcePointer + 2] & 0xF) << 8) | CompressedData[SourcePointer + 3]) + 1;
                                    Amount   = (((CompressedData[SourcePointer] & 0xF) << 12) | (CompressedData[SourcePointer + 1] << 4) | (CompressedData[SourcePointer + 2] >> 4)) + 273;
                                    SourcePointer += 4;
                                    break;
                                }
                                default: { // 2 bytes
                                    Distance = (((CompressedData[SourcePointer] & 0xF) << 8) | CompressedData[SourcePointer + 1]) + 1;
                                    Amount   = (CompressedData[SourcePointer] >> 4) + 1;
                                    SourcePointer += 2;
                                    break;
                                }
                            }

                            // Copy the data
                            for (j = 0; j < Amount; j++)
                                DecompressedData[DestPointer + j] = DecompressedData[DestPointer - Distance + j];
                            DestPointer += (uint)Amount;
                        }

                        // Check for out of range
                        if (SourcePointer >= CompressedSize || DestPointer >= DecompressedSize)
                            break;
                    }
                }
    return(DestPointer);
}



// no problems with the starting point of compressed data here
int puyo_prs_unpack(byte *compressedData, int compressedSize, byte *decompressedData, int decompressedSize) {
    int     i,
            j;
                uint Cpointer = 0x0; // Compressed Pointer
                uint Dpointer = 0x0; // Decompressed Pointer

                while (Cpointer < compressedSize && (Dpointer < decompressedSize || decompressedSize == 0))
                {
                    byte Cflag = compressedData[Cpointer];
                    Cpointer++;

                    for (i = 0; i < 8; i++)
                    {
                        /* Is the data compressed? */
                        if ((Cflag & (1 << i)) > 0)
                        {
                            /* No */
                            decompressedData[Dpointer] = compressedData[Cpointer];
                            Cpointer++;
                            Dpointer++;
                        }
                        else
                        {
                            /* Yes */
                            i++;
                            if (i >= 8)
                            {
                                i = 0;
                                Cflag = compressedData[Cpointer];
                                Cpointer++;
                            }

                            /* How will we copy this? */
                            uint offset, amountToCopy;
                            if ((Cflag & (1 << i)) > 0)
                            {
                                byte first  = compressedData[Cpointer];
                                byte second = compressedData[Cpointer + 1];
                                Cpointer += 2;

                                /* Make sure we are not out of range */
                                if (Cpointer >= compressedSize)
                                    break;

                                offset = (uint)((second << 8 | first) >> 3) | 0xFFFFE000;
                                amountToCopy = first & (uint)0x7;

                                if (amountToCopy == 0)
                                {
                                    amountToCopy = (uint)compressedData[Cpointer] + 1;
                                    Cpointer++;
                                }
                                else
                                    amountToCopy += 2;
                            }
                            else
                            {
                                amountToCopy = 0;
                                for (j = 0; j < 2; j++)
                                {
                                    i++;
                                    if (i >= 8)
                                    {
                                        i = 0;
                                        Cflag = compressedData[Cpointer];
                                        Cpointer++;
                                    }
                                    offset = (amountToCopy << 1);
                                    amountToCopy = offset | (uint)((Cflag & (1 << i)) > 0 ? 0x1 : 0x0);
                                }
                                offset = (compressedData[Cpointer] | 0xFFFFFF00);
                                amountToCopy += 2;
                                Cpointer++;
                            }

                            /* Now copy the data */
                            for (j = 0; j < amountToCopy; j++)
                                decompressedData[Dpointer] = decompressedData[(int)(Dpointer + offset + j)];

                            Dpointer += amountToCopy;
                        }

                        /* Make sure we are not out of range */
                        if (Cpointer >= compressedSize || (Dpointer >= decompressedSize && decompressedSize != 0))
                            break;
                    }
                }
    return(Dpointer);
}


/*
// the compressed data must start from offset 0x4!
// uint decompressedSize = data.ReadUInt(0x0);
int puyo_pvz_unpack(byte *compressedData, int compressedSize, byte *decompressedData, int decompressedSize) {
    int     i,
            j;
                uint Cpointer = 0x0; // Compressed Pointer  // was 0x4
                uint Dpointer = 0x0; // Decompressed Pointer

                // This file heavily relies on VrSharp
                // Check to see if this is a valid PVR file
                Images images = new Images(data.Copy(0x4, (int)data.Length - 4), null);
                if (images.Format != GraphicFormat.PVR)
                    return(-1); //throw new Exception();

                // Get correct file offset
                int FileOffset = (data.ReadString(0x4, 4) == "GBIX" ? 0x10 : 0x0);

                PvrPixelCodec PaletteCodec = PvrCodecs.GetPixelCodec(data.ReadByte(FileOffset + 0xC));
                PvrDataCodec DataCodec     = PvrCodecs.GetDataCodec(data.ReadByte(FileOffset + 0xD));
                if (PaletteCodec == null || DataCodec == null)
                    throw new Exception();

                DataCodec.Decode.Initialize(0, 0, PaletteCodec.Decode);
                int ChunkSize = (DataCodec.Decode.GetChunkBpp() / 8);

                // Copy the first 16/32 bytes
                for (int i = 0; i < FileOffset + 0x10; i++)
                {
                    decompressedData[Dpointer] = compressedData[Cpointer];
                    Dpointer++;
                    Cpointer++;
                }

                // Ok, let's decompress the data
                while (Cpointer < compressedSize && Dpointer < decompressedSize)
                {
                    int copyAmount = compressedData[Cpointer + ChunkSize] + 1;

                    for (int i = 0; i < copyAmount; i++)
                        Array.Copy(compressedData, Cpointer, decompressedData, Dpointer + (i * ChunkSize), ChunkSize);

                    Cpointer += (uint)(ChunkSize + 1);
                    Dpointer += (uint)(copyAmount * ChunkSize);
                }
    return(Dpointer);
}
*/

