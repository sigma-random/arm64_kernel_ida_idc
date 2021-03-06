#include <idc.idc>

static main() {

  auto fd_kallsyms;

  auto kallsyms_file = AskFile(0, "*.map", "Select kallsyms file");

  Message("%s\n", kallsyms_file);

  fd_kallsyms = fopen(kallsyms_file, "r");

  if( fd_kallsyms == 0 ) {
    Message("open %s failed!\n", kallsyms_file);
    return;
  }
  while(1) {
    auto line = readstr(fd_kallsyms);
    auto line_len = strlen(line);
    if( line == -1 )
	break;
    auto addr_str = line[10:26];
    auto name_len = line_len - 20;
    auto func_name = substr(line, 33, 33+name_len);
    func_name = func_name[0:-1];
    //print(addr_str);
    //print(func_name);
    auto addr = xtol(addr_str);
    Message("%s = %x\n", func_name, addr);
    if( addr == 0 )
      continue;
    MakeName(addr, func_name);
    MakeFunction(addr,BADADDR);
  }

  fclose(fd_kallsyms);

}