# mi-thermal-crypt

Encrypt or decrypt thermal configs used by mi-thermald on all Xiaomi devices.
You can use this to decrypt, for example, `thermal-normal.conf`, edit it and then encrypt it back (mi-thermald accepts only encrypted thermal configs, not plain text).

```
Usage: mi-thermal-crypt [OPTION]...
Encrypt/decrypt mi_thermald configs

  -h, --help            Print help and exit
  -V, --version         Print version and exit
  -i, --infile=STRING   Input filename
  -o, --outfile=STRING  Output filename
  -e, --encrypt         Encrypt input plain text file to output file
                          (default=off)
```

To compile it yourself:
```
gcc mi-thermal-crypt.c cmdline.c -o mi-thermal-crypt -lssl -lcrypto
```

### TODO
- Convert to Python or something
