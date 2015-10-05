# Perfect Spatial Hashing - C++ Implementation #

## Abstract ##
_This project gives a C++ implementation of Perfect Spatial Hashing, based on [Sylvain Lefebvre and Hugues Hoppe's paper](http://perfecthashing.googlecode.com/files/perfecthash.pdf) from Microsoft Research._


## Examples ##

|<p align='center'><b>Original picture</b></p>|<p align='center'><b>Hash table</b></p>|<p align='center'><b>Offset table</b></p>|<p align='center'><b>Original size</b></p>|<p align='center'><b>Compressed size</b></p>|<p align='center'><b>Compression ratio</b></p>|
|:--------------------------------------------|:--------------------------------------|:----------------------------------------|:-----------------------------------------|:-------------------------------------------|:---------------------------------------------|
|![http://perfecthashing.googlecode.com/svn/trunk/data/sample.jpg](http://perfecthashing.googlecode.com/svn/trunk/data/sample.jpg)|![http://perfecthashing.googlecode.com/svn/trunk/output/Sample%20-%20Hash%20Table.jpg](http://perfecthashing.googlecode.com/svn/trunk/output/Sample%20-%20Hash%20Table.jpg)|<img src='http://perfecthashing.googlecode.com/svn/trunk/output/Sample%20-%20Offset%20Table.jpg' align='center' />| 492\*492\*1\*8 bits <br /> = 242064 bytes <br /> = **237 KB** | **Hash table:**<br /> 115\*115\*1\*8 bits <br /><br /> **Offset Table:**<br /> 71\*71\*2\*8 bits <br /> <br /> **Mask:** <br /> 115\*115 bits <br /> <br /> **TOTAL:**<br>  199681 bits <br />= 249661 bytes <br />= <b>25 KB</b> <br />  <table><thead><th> <b>10.5 %</b>                                </th></thead><tbody>
<tr><td><img src='http://perfecthashing.googlecode.com/svn/trunk/data/Color%20dots.jpg' /></td><td><img src='http://perfecthashing.googlecode.com/svn/trunk/output/Color%20dots%20-%20Hash%20Table.jpg' /></td><td><img src='http://perfecthashing.googlecode.com/svn/trunk/output/Color%20dots%20-%20Offset%20Table.jpg' align='center' /></td><td> 270*271*3*8 bits <br /> = 219510 bytes <br /> = <b>214 KB</b> </td><td> <b>Hash table:</b><br /> 114*114*3*8 bits <br /><br /> <b>Offset Table:</b><br /> 71*71*2*8 bits <br /> <br /> <b>Mask:</b> <br /> 114*114 bits <br /> <br /> <b>TOTAL:</b><br>  405556 bits <br />= 50695 bytes <br />= <b>50 KB</b> <br /> </td><td> <b>23.4 %</b>                                </td></tr></tbody></table>

