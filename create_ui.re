= UIの作成

@<chap>{create_uiless_addon}ではアドオンの機能部分を作成しました。
本章では、さきほどのアドオンにUIを追加します。

== パネルクラスの追加

3D ViewportとOutlinerの間にあるタブに紐づいて表示されているウィンドウをパネルと呼びます。
"weight_picker.py"に次のコードを追記してください。
追加したコードの意味はコメントとしてコード内に付与しています。

//list[][][python]{
# パネルの定義
class WeightPickerPanel(bpy.types.Panel):
    bl_space_type  = "VIEW_3D"
    bl_region_type = "UI"
    bl_category    = "Tool" # Toolタブに追加
    bl_idname      = "VIEW3D_PT_weightpicker_setweight"
    bl_label       = "Set Weight"
    bl_context     = ""
    bl_options     = {"HEADER_LAYOUT_EXPAND"}

    # パネルの表示条件
    @classmethod
    def poll(cls, context):
        if context.mode == 'PAINT_WEIGHT': # Weight Paint Modeなら...
            return True  # 表示
        else:                              # そうでなければ...
            return False # 非表示

    # 描画するUIの定義
    def draw(self, context):
        # 要素を縦に並べる
        col = self.layout.column()

        # Weightを1に設定するボタン
        col.operator("weightpicker.set_weight", text="Weight: 1.0").weight = 1.0

        # Weightを0.8に設定するボタン
        col.operator("weightpicker.set_weight", text="Weight: 0.8").weight = 0.8

        # Weightを0.5に設定するボタン
        col.operator("weightpicker.set_weight", text="Weight: 0.5").weight = 0.5

        # Weightを0.2に設定するボタン
        col.operator("weightpicker.set_weight", text="Weight: 0.2").weight = 0.2
//}

パネルを表示させるために@<code>{register()}関数と@<code>{unregister()}関数も更新します。

//list[][][python]{
def register():
    bpy.utils.register_class(WeightPicker)
    bpy.utils.register_class(WeightPickerPanel)   # add

def unregister():
    bpy.utils.unregister_class(WeightPicker)
    bpy.utils.unregister_class(WeightPickerPanel) # add
//}

以上で更新作業は完了です。
最終的なコードは次のようになりました。

//list[][][python]{
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

    weight: bpy.props.FloatProperty()

    def execute(self, context):
        bpy.data.scenes["Scene"].tool_settings \
        .unified_paint_settings.weight = self.weight
        return {'FINISHED'}

class WeightPickerPanel(bpy.types.Panel):
    bl_space_type  = "VIEW_3D"
    bl_region_type = "UI"
    bl_category    = "Tool"
    bl_idname      = "VIEW3D_PT_weightpicker_setweight"
    bl_label       = "Set Weight"
    bl_context     = ""
    bl_options     = {"HEADER_LAYOUT_EXPAND"}

    @classmethod
    def poll(cls, context):
        if context.mode == 'PAINT_WEIGHT':
            return True
        else:
            return False

    def draw(self, context):
        col = self.layout.column()

        col.operator("weightpicker.set_weight", text="Weight: 1.0").weight = 1.0
        col.operator("weightpicker.set_weight", text="Weight: 0.8").weight = 0.8
        col.operator("weightpicker.set_weight", text="Weight: 0.5").weight = 0.5
        col.operator("weightpicker.set_weight", text="Weight: 0.2").weight = 0.2

def register():
    bpy.utils.register_class(WeightPicker)
    bpy.utils.register_class(WeightPickerPanel)

def unregister():
    bpy.utils.unregister_class(WeightPicker)
    bpy.utils.unregister_class(WeightPickerPanel)

if __name__ == "__main__":
    register()

//}

それでは、アドオンを再インストールして結果を確認してみましょう。

//image[result][実行結果]{
//}

うまくいったようです。ボタンでWeightの設定値も変更できますし、
Weight Paint Mode以外に切り替えるとパネルは見えなくなります。

== まとめ

アドオンにUIを実装し、ボタンから機能を呼び出すことができました。
これによって、直感的にアドオンが使用でき、Quick Favoritesへの登録もできるようになりました。
より高度な機能を実装したい方のために、付録として開発に関するTipsをまとめます。
