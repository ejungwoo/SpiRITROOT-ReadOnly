{
  SysInfo_t info;
  gSystem -> GetSysInfo(&info);
  TString osString = info.fOS;

  TString libString;
  if (osString.Index("Darwin") >= 0)
    libString = "/Users/ejungwoo/spiritroot-readonly/build/libSpiRIROOT-ReadOnly.dylib";
  else if (osString.Index("Linux") >= 0)
    libString = "/Users/ejungwoo/spiritroot-readonly/build/libSpiRIROOT-ReadOnly.so";

  if (gSystem -> Load(libString) != -1)
    cout << "++ SpiRITROOT-ReadOnly ++" << endl;
  else
    cout << "FAILED loading SpiRITROOT-ReadOnly" << endl;
}
