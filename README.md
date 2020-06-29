To use the combine-data and print-to-txt program, you should load the latest gcc module.

The combine excutable accept the commands like:
./combine_* [combined_file_name] [files_to_be_combined]
the combined_file_name should only be one argument, files_to_be_combined are not limites, but you should specify tsep, mom for building_blocks(files with different mom or tsep cannot be combined, the strings in files_to_be_combined should only be different in configuration number with each other)
For example:
./combine_* pion1_3pt_m-0.075_im-0.075_t6_p0 kaon_pdf3pt*.pion_1_m-0.075_im-0.075_*_t6_p0.*.iog

The print-to-txt executable accept the command like:
./print (-gN) (-qQ) [combined_file_name]
here the option -gN specifies the operator we want, -qQ specifies the momentum we want. In our case, N=8. the following argument should be the combined file.
If the option is ommitted, N is set to its default value -1 and all operators will be printed.
Note that the output files has the same name prefix as [combined_file_name], so it will be generated in the same directory as the [combined_file_name], no matter where you execute the print ptogram. You'd better make a new directory and move the combined files to it first.


print_all_hadpsec is to print the data and cfg list, because it's used to print a combined data without sorting the cfg numbers.
combine_all_cfgs is to combine all files faster, without checking indices and sorting cfgs.
