echo "Sprawdzanie objętości źródeł..."
du -csh --apparent-size ./src/* ./*.c ./*.asm ./Makefile | grep total 

echo "Sprawdzanie objętości interfejsu..."
du -csh --apparent-size ./src/ui/* | grep  total

echo "Sprawdzanie objętości skompilowanych składników"
du -csh --apparent-size ./out/* | grep total

echo "Sprawdzanie objętości kernela"
du -sh --apparent-size ./kernel.bin

