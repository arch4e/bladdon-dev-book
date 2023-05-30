= UIのないアドオンの制作

本章では、キーボードショートカットによってBlenderの操作を呼び出すアドオンを作成します。
コーディングの手間が少なく、知っていると役立ちそう（取り組むモチベーションを維持しやすそう）な課題にしました。

本章を読み終える頃には、キーボードショートカットに登録できない機能を
キーボードショートカットで呼び出せるようにしたり、複数の操作を1つのキーボードショートカットで
呼び出したりすることができるようになります。

== アドオン化する処理の決定

今回は一例として、Weight Paint Modeのブラシに設定されている
Weightの値をキーボードショートカットで変更することを目標にします。
具体的には、キーボードショートカットでWeightを1、0.8、0.5、0.2に設定できるようにします。

//image[weight][アドオンで操作するWeightの値]{
//}

== コードの調査

目的とする処理を実際に行うためのコードを調べます。
公式ドキュメント@fn{document}を参照したほうが正確ですが、
機能の紹介も兼ねてBlenderのUIから辿ってみます。

PreferenceのInterface欄に、"Python Tooltips"というオプションがあります。
このオプションを有効にすることで、UIにマウスカーソルを当てたとき、
対応するPythonのプロパティ（設定値などの情報）やメソッド（移動や削除などの処理）が表示されます。

//image[python_tooltips][Python Tooltips]{
//}

試しに、Weightの値にマウスカーソルを当ててみると、次のように表示されます。

//image[weight_python_tooltip][Weightの設定値が格納されているプロパティ]{
//}

@<code>{bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight}と表示されています。
Scriptingタブに移動し、Python Consoleで上記のプロパティを呼んでみると、ブラシに設定されているWeightの値が表示されます。

//image[console_output_1][Weightの設定値が格納されているプロパティ]{
//}

Weightの値を手動で変更し、さきほどのプロパティをもう一度呼んでみると、
設定値に対応して出力が変化していることがわかります。
また、Infoエリアを見るとWeightを変更した際のログが出力されていることがわかります。

//image[console_output_2][Weightの設定値変更して、再度プロパティの値を参照した結果]{
//}

Infoエリアのログをコピーし、値だけ0.2に変更して実行するとどうなるでしょうか。

//image[set_weight_via_console][Weightの設定値をスクリプトで変更した結果]{
//}

スクリーンショットの通り、ブラシに設定されているWeightが0.2になりました。

以上でアドオンに実装したい処理に対応するコードを見つけることができました。
より正確に調べるためには、公式ドキュメントで見つけたキーワードを検索し
関連情報を確認するとよいでしょう。

== アドオンの作成

前の節で見つけたコードをアドオンの形にしていきます。
テキストエディタで新しいファイルを作成し、次のコードを書き込んでください。
書き終わったら、ファイルを"weight_picker.py"という名前で任意の場所に保存してください。

//listnum[weight_picker][][python]{
import bpy

bl_info = {
    "name"   : "Weight Picker",
    "author" : "arch4e",
    "version": (1, 0),
    "blender": (3, 0, 0)
}

class WeightPicker(bpy.types.Operator):
    bl_idname = 'weightpicker.set_weight'
    bl_label  = 'Weight Picker'

    def execute(self, context):
        bpy.data.scenes["Scene"].tool_settings \
        .unified_paint_settings.weight = 0.5
        return {'FINISHED'}

def register():
    bpy.utils.register_class(WeightPicker)

def unregister():
    bpy.utils.unregister_class(WeightPicker)

if __name__ == "__main__":
    register()

//}

アドオンを実行する前にコードの解説をします。
Pythonのコードはインデント（字下げ）が重要な意味を持ちます。
基本的に、波括弧で囲まれていたり行頭が揃っている範囲がひとつのかたまりです。
先ほどのコードをかたまりごとに色付けすると次のようになります。

//image[code][処理のかたまりごとに色付けしたコード]{
//}

1行目は@<chap>{basic_knowledge}で扱った、bpyモジュールの読み込みです。

3~8行目はアドオンの情報を定義しており、上からアドオン名、作者、アドオンバージョン、
サポートするBlenderのバージョンです。
"サポートする"といっても禁止処理を書かなければ、Blenderのバージョン次第では
アドオンを使用できます。

10~17行目が本アドオンのメイン部分です。"クラス"と呼ばれる、データのかたまりとして定義されています。
@<code>{bl_idname}で機能を呼び出すときの名前を、@<code>{bl_label}でその機能のラベルを定義します。
そして、処理が呼び出されたときの動作を定義しているのが@<code>{execute}から始まるブロックです。
処理内容は前節で確認したコードを使用し、Weightを0.5に設定しています。
今のコードでは0.5以外の値には対応していませんが、動作確認後にスクリプトをアップデートします。
最後に、呼び出し元に@<code>{'FINISHED'}を返して処理は終了です。
このコードでは使用されていませんが、処理を中断するケースでは@<code>{'CANCELED'}を返し、
呼び出し元に対して処理が途中で止まったことを明示します。

19~23行目がアドオンのインストール/アンインストール時に実行される処理です。
定義したクラスは@<code>{bpy.utils.register_class}を使用して登録する必要があり、
アドオンインストール時に呼び出される@<code>{register()}関数内でそれを行なっています。
アンインストール時の処理はその逆です。

25~26行目は、まず触ることはないため忘れて問題ありません。
この手の"書いてあるけど説明するタイミングではない"コードを"おまじない"と呼ぶことがあります。

== アドオンの動作確認

それでは、作成したアドオンをBlenderにインストールし、実行してみましょう。
インストール方法は他のアドオンと同様に、Edit → Preference → Add-onsからインストールします。
インストールできない方は、System Consoleを見るとエラーが表示されているかもしれません。
（@<chap>{basic_knowledge}で開き方を解説しています。）

//image[install_button]["Install"からファイルを選ぶ]{
//}

インストールできたら、アドオンにチェックを入れて有効化し
Python Consoleでアドオンの機能を呼び出してみましょう。

//list[python_console][][python]{
# Weight設定前の値
bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight

# アドオンによるWeight変更
bpy.ops.weightpicker.set_weight()

# Weight設定後の値
bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight
//}

//image[result_1][実行結果]{
//}

無事に、アドオンでWeight値を変更することができました。
現在は設定値が0.5固定ですが、他の値も設定できるように変更したあと
キーボードショートカットの設定をしてこの章は終了です。

== アドオンの拡張

キーボードショートカットの設定をする前に、
0.5以外の値も設定できるようにしましょう。
次のようにコードを変更してください。
変更箇所はコメントを振っている14行目、18行目です。

//listnum[updated_weight_picker][][python]{
import bpy

bl_info = {
    "name"   : "Weight Picker",
    "author" : "arch4e",
    "version": (1, 0),
    "blender": (3, 0, 0)
}

class WeightPicker(bpy.types.Operator):
    bl_idname = 'weightpicker.set_weight'
    bl_label  = 'Weight Picker'

    weight: bpy.props.FloatProperty() # add

    def execute(self, context):
        bpy.data.scenes["Scene"].tool_settings \
        .unified_paint_settings.weight = self.weight # change
        return {'FINISHED'}

def register():
    bpy.utils.register_class(WeightPicker)

def unregister():
    bpy.utils.unregister_class(WeightPicker)

if __name__ == "__main__":
    register()

//}

データのやり取りをするためのプロパティとして@<code>{weight}を定義します。
コロン（@<code>{:}）から左がプロパティ名、右はデータの種類を指定します。
今回は小数点を扱うため、@<code>{bpy.props.FloatProperty()}を使用します。
これが整数値であれば@<code>{bpy.props.IntProperty()}、文字列であれば@<code>{bpy.props.StringProperty()}となります。
詳細は公式ドキュメント@<fn>{document_props}を参照してください。

スクリプトを更新したらアドオンを再インストールし、動作確認をします。
変更前と異なり、@<code>{weightpicker.set_weight()}の呼び出し時に@<code>{weight}を指定してください。
指定した値にWeightの値が更新されていれば、動作確認は成功です。

//list[python_console][][python]{
# Weightの確認
bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight

# Weightを0.8に設定
bpy.ops.weightpicker.set_weight(weight=0.8)

# Weightの確認
bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight

# Weightを0.5に設定
bpy.ops.weightpicker.set_weight(weight=0.5)

# Weightの確認
bpy.data.scenes["Scene"].tool_settings.unified_paint_settings.weight
//}

//image[result_2][実行結果]{
//}

//footnote[document_props][ https://docs.blender.org/api/current/bpy.props.html ]

== キーボードショートカットの登録

機能の実装は完了したため、キーボードショートカットに登録します。
登録方法を下記に示します。

  1. Preference → Keymapと進み、Weight Paint → Weight Paint (Global)で"+ Add New"を選ぶ
  2. "none"となっている項目をクリックし、@<code>{weightpicker.set_weight}を指定する
  3. キーボードショートカットのトリガーとなるキーを設定する
  4. 呼び出された際に設定するWeightの値を入力する

//image[set_keymap_1][キーボードショートカットの登録 - 1.1]{
//}

//image[set_keymap_2][キーボードショートカットの登録 - 1.2]{
//}

//image[set_keymap_3][キーボードショートカットの登録 - 2]{
//}

//image[set_keymap_4][キーボードショートカットの登録 - 3,4]{
//}

設定が完了したら、Weight Paint Modeで実際にキーボードショートカットを使ってみましょう。
正しく設定できていれば、キーボードショートカットでWeightの値を変更できます。
以上で、本章の作業は終了です。

== まとめ

本章では、Weight Paint ModeにおけるブラシのWeight値変更という動作を題材とし、
機能の実装とキーボードショートカットの設定を行いました。
同じ方法で、キーボードショートカットに対応していない操作をキーボードショートカットに登録できるようにしたり、
@<code>{execute()}内の記述を足すことでキーボードショートカット1つで複数の操作をまとめて実行することができるようになります。

次の章では、アドオンにUIを実装し、ボタンで機能を呼び出せるようにします。

//footnote[document][ https://docs.blender.org/api/current/index.html ]
