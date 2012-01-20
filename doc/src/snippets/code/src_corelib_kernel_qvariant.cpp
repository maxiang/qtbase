/****************************************************************************
**
** Copyright (C) 2012 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: http://www.qt-project.org/
**
** This file is part of the documentation of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Nokia Corporation and its Subsidiary(-ies) nor
**     the names of its contributors may be used to endorse or promote
**     products derived from this software without specific prior written
**     permission.
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
** $QT_END_LICENSE$
**
****************************************************************************/

//! [0]
QDataStream out(...);
QVariant v(123);                // The variant now contains an int
int x = v.toInt();              // x = 123
out << v;                       // Writes a type tag and an int to out
v = QVariant("hello");          // The variant now contains a QByteArray
v = QVariant(tr("hello"));      // The variant now contains a QString
int y = v.toInt();              // y = 0 since v cannot be converted to an int
QString s = v.toString();       // s = tr("hello")  (see QObject::tr())
out << v;                       // Writes a type tag and a QString to out
...
QDataStream in(...);            // (opening the previously written stream)
in >> v;                        // Reads an Int variant
int z = v.toInt();              // z = 123
qDebug("Type is %s",            // prints "Type is int"
        v.typeName());
v = v.toInt() + 100;            // The variant now hold the value 223
v = QVariant(QStringList());
//! [0]


//! [1]
QVariant x, y(QString()), z(QString(""));
x.convert(QVariant::Int);
// x.isNull() == true
// y.isNull() == true, z.isNull() == false
//! [1]


//! [2]
QVariant variant;
...
QColor color = variant.value<QColor>();
//! [2]


//! [3]
QColor color = palette().background().color();
QVariant variant = color;
//! [3]


//! [4]
QVariant v;

v.setValue(5);
int i = v.toInt();         // i is now 5
QString s = v.toString()   // s is now "5"

MyCustomStruct c;
v.setValue(c);

...

MyCustomStruct c2 = v.value<MyCustomStruct>();
//! [4]


//! [5]
QVariant v;

MyCustomStruct c;
if (v.canConvert<MyCustomStruct>())
    c = v.value<MyCustomStruct>();

v = 7;
int i = v.value<int>();                        // same as v.toInt()
QString s = v.value<QString>();                // same as v.toString(), s is now "7"
MyCustomStruct c2 = v.value<MyCustomStruct>(); // conversion failed, c2 is empty
//! [5]


//! [6]
QVariant v = 42;

v.canConvert<int>();              // returns true
v.canConvert<QString>();          // returns true

MyCustomStruct s;
v.setValue(s);

v.canConvert<int>();              // returns false
v.canConvert<MyCustomStruct>();   // returns true
//! [6]


//! [7]
MyCustomStruct s;
return QVariant::fromValue(s);
//! [7]


//! [8]
QObject *object = getObjectFromSomewhere();
QVariant data = QVariant::fromValue(object);
//! [8]
