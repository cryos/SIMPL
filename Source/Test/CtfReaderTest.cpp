/* ============================================================================
 * Copyright (c) 2011, Michael A. Jackson (BlueQuartz Software)
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright notice, this
 * list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright notice, this
 * list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * Neither the name of Michael A. Jackson nor the names of its contributors may
 * be used to endorse or promote products derived from this software without
 * specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE
 * USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */


#include <string.h>

#include "H5Support/H5Lite.h"
#include "H5Support/H5Utilities.h"


#include "EbsdLib/HKL/CtfReader.h"
#include "EbsdLib/HKL/H5CtfImporter.h"

int main(int argc, char **argv)
{

  std::string ctfFile("/Users/Shared/Data/HKL_Data/Project4.ctf");

  CtfReader reader;
  reader.setFileName(ctfFile);

  int err =  reader.readFile();
  if (err < 0)
  {
    std::cout << "Error reading .ctf file" << std::endl;
    return EXIT_FAILURE;
  }

  reader.printHeader(std::cout);
  std::cout << "Success Reading the .ctf File" << std::endl;


  std::cout << "-- Testing the H5CtfImporter..." << std::endl;
  std::string h5File = "/tmp/out.h5ctf";
  hid_t fileId = H5Utilities::createFile(h5File);

  // Test out the HDF5 Importer
  H5CtfImporter::Pointer importer = H5CtfImporter::New();
  importer->importFile(fileId, 0, ctfFile);


  H5Utilities::closeFile(fileId);

  std::cout << "Done Testing Ctf Reader" << std::endl;
  return EXIT_SUCCESS;
}
