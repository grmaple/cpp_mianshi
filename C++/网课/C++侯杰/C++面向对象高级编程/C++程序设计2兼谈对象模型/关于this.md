## 关于this

简单来说，你通过一个对象来调用一个函数。那个对象的地址就是this

虚函数两个用法，一是多态，一是模板方法。

![image-20200830093808873](C:\Users\xuyingfeng\AppData\Roaming\Typora\typora-user-images\image-20200830093808873.png)

A类先构造好框架，然后把没写好的写成虚函数。B在定义虚函数的内容。

CDyDoc myDoc;//子类对象

myDoc.OnFileOpen();//调用父类函数

//myDoc.CDocument::OnFileOpen(&myDoc);

OnFileOpen(&myDoc)内部调用Serialize(this);this就是&myDoc

相当于this->Serialize();this指向子类对象，符合向上转型。

相当于(*(this->vptr)[n])(this);动态绑定。

