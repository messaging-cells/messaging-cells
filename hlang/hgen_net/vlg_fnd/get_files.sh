
rm ./calc_redun.v
rm ./debouncer.v
rm ./hglobal.v
rm ./hnull_sink.v
rm ./hnull_source.v
rm ./nd_1to2.v
rm ./nd_2to1.v
rm ./pakin.v
rm ./pakout.v
rm ./tree_nand.v

cp ../../vl_tests/common/* .
cp ../../vl_tests/t5_nd_1to2/rtl/nd_1to2.v .
cp ../../vl_tests/t6_nd_2to1/rtl/nd_2to1.v .
cp ../../vl_tests/t7_pakout/rtl/pakout.v .
cp ../../vl_tests/t8_pakin/rtl/pakin.v .

