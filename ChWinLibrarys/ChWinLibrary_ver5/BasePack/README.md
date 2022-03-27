# ChBaseライブラリ

##内容

ChBaseライブラリはChライブラリ全体のベースとなる機能をまとめたライブラリです。<br>
利用する場合はChLibraryのいずれかをインクルードしてください。<br>


ChBaseライブラリは以下のnamespaceが存在します。
- ChStd<br>
基本となる機能群
- ChPtr<br>
ポインターに関する機能群
- ChFIO<br>
ファイルの入出力に関する機能群<br>
※ChFIOはChCppライブラリへ移動する予定
- ChStr<br>
文字列に関する機能群
- ChMath<br>
数学的な機能群
- Ch3DMath<br>
3Dで利用する際に使用する数学的な機能群
- Ch3D<br>
3Dモデルの構成など数学的以外の部分の機能群<br>
※作成・適応途中

##主な便利機能

##### ChStd

- EnumCast
EnumCastは引数にenumを与えると、数値を出力します。<br>
この機能を利用すると、enum classから数値を取得することが容易になります。<br>

~~~
enum class Test : unsighned char {A,B,C};

unsigned char tmp = ChStd::EnumCast(Test);
~~~

##### ChPtr

- Shared<br>
std::shared_ptrの型名を短縮した形になります<br>

- Make_S<br>
std::make_sharedの関数名を短縮した形になります。<br>

~~~
ChPtr::Shared<long long> tmp = ChPtr::Make_S<long long>(0);
~~~

- NullChake<br>
対象のポインタがNULLまたはnullptrであることを確認します。<br>

~~~
int *tmp = nullptr;

if(ChPtr::NullChake(tmp))return;

~~~

- SafeCast<br>
dynamic_castの関数名を短縮した形になります。

~~~

class A{};

class B:public A{};

class C:public A{};

A* tmp1 = new C();
A* tmp2 = new B();

B* test = ChPtr::SafeCast<B>(tmp1);//NG return nullptr

B* test = ChPtr::SafeCast<B>(tmp2);//OK return tmp2

~~~

##### ChFIO

- File<br>
Fileクラスは入出力を扱う機能をパック化したものです。<br>

FileOpenメソッドを呼ぶときの第二引数はopen modeを指定できます。<br>
open modeの既定の引数はstd::ios::inとstd::ios::outとなります。<br>
std::ios::inが指定されていた場合、ファイルが存在しない場合にエラーとなってしまうため、エラーを回避するためにstd::ios::addが追加されます。<br>
~~~
ChFIO::File flie;

file.FileOpen("Test.txt");
~~~

FileReadメソッドはFileから取り込んだ文字列をすべて出力します。<br>
逆にFileWriteメソッドはFileへ指定した文字列を入力します。<br>

##### ChMath
- Vector3Base,Vector2Base,MatrixBase4x4<br>
変数の型を指定して利用できる数学的機能が組み込まれた機能です。<br>
ChVec3やChVec2,ChLMatやChRMatなどに利用されています。<br>

~~~
Vector3Base<float> vec;

//ベクトルの長さを取得。
vec.val.GetLen();

//ベクトルの長さを1にします。※Normalは法線(面の向き)の事。
vec.val.Normalize();

//ベクトルの各要素の値を絶対値にします。
vec.val.Abs();

MatrixBase4x4<float> mat;
//単位行列にします。
mat.Identity();

//逆行列を作ります。
mat.Inverse();

//行列とベクトルを掛け合わせて新しいベクトルを作ります※1
mat.HorizontalMul(vec);

~~~

※1:<br>
HorizontalMulは横軸ベクトルに行列をかけて縦軸ベクトルを出力します。<br>
VerticalMulは縦軸のベクトルに行列をかけて横軸ベクトルを出力します。<br>

- VectorBase,MatrixBase<br>
数学的計算機能の本体になります。<br>
VectorBaseもMatrixBaseもこれらをもとに何か別のクラスを作成することに利用します。<br>

~~~

//VectorBaseの配列に別の変数と値を共有する。//
//x == VectorBase.val[0], y == VectorBase.val[1], z == VectorBase.val[2];//
//unionを利用する場合はコンストラクタや演算子オーバーロードを自身で設定する必要がある。//
class TestVector3
{
	union
	{
		struct{float x,y,z;};
		VectorBase<float> val;
	};
}

//MatrixBaseをパック化//
class TestMatrix:public MatrxBase<float,4,4>{};

~~~

##### Ch3DMath

- ChVec3,ChVec2,ChLMat,ChRMat
ChVec3,ChVector3はDirectXでいうD3DXVECTOR3やXMFloat3,OpenGLでいうGLFloat3と同じ立ち位置である。<br>
ChVec2,ChVector2はDirectXでいうD3DXVECTOR2やXMFloat2,OpenGLでいうGLFloat2と同じ立ち位置である。<br>

ChLMat,ChLMatrixは左手座標系を元に位置情報や回転情報などを情報を行列の各数値に割り当てて利用します。<br>
※3Dの概念には左手座標系と右手座標系と呼ばれるものがあります。DirectXは基本的に左手座標系です。
 
##### ChStr

- GetFloatingFromText<br>
この関数は数値が書かれている文字列で入れられた数値を浮動小数点型へ変換する関数です。

~~~

float tmp = ChStr::GetFloatingFromText<float>("0.125");//tmp == 0.125

~~~

- RemoveToUnNums
この関数は文字列内の数値となる文字("01234567899",'.','-')以外の文字を取り除く関数です。

~~~

std::string tmp = ChStr::RemoveToUnNums("+-128.90");//tmp == "-128.90"//

~~~

