สำหรับ code ต่อไปนี้เพื่อความง่ายต่อการทดสอบผมจึงมี demo ใน google colab [ในลิงค์นี้](https://colab.research.google.com/github/ohmreborn/os_homework/blob/main/1_parallel_6610501963/parallel_demo.ipynb) สำหรับข้อแรก ซึ่งจะมีคำสั่งทุกอย่างเตรียมให้แล้ว สามารถ ข้ามไปอ่านใน colab ได้เลย

# compile code
```
make
```

# run code
โดยสามารถ recompile ให้โดยอัตโนมัติ โดยไม่ต้อง พิมพ์ว่า make ใหม่อีกรอบ
```
make run
```
สามารถใส่ขนาดของ memory ที่อยากจะจองได้ เช่น 60MB ให้ใส่คำว่า MEM=60 ต่อท้าย
```
make run MEM=60
```

กรณี อยากลองทสอบ memory หลายครั้ง ให้ใช้ script ที่เตรียมไว้ให้ 
```
./run.sh
```