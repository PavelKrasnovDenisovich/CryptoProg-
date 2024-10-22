#include <iostream>
#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/files.h>
#include <cryptopp/md5.h>
#include <string>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

using namespace std;
using namespace CryptoPP;
int main(int argc, char **argv)
{
  string Hash;
  Weak::MD5 hash;
  FileSource("test.txt", true, new HashFilter(hash, new HexEncoder(new StringSink (Hash))));
  cout<<Hash<<endl;
  return 0;
}
