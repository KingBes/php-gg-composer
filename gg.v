module main

import gg

import gx


@[export: 'to_string']
fn to_string(str &char) string {
	return unsafe { str.vstring() }
}

@[export: 'to_color']
fn to_color(r u8,g u8,b u8 ,a u8) gx.Color
{
    return gx.rgba(r,g,b,a)
}

@[export: 'new_context']
fn new_context(configs gg.Config) &gg.Context {
	return gg.new_context(configs)
}

@[export: 'begin']
fn begin(mut ctx gg.Context)
{
    ctx.begin()
}

@[export: 'run']
fn run(mut ctx gg.Context) {
	ctx.run()
}

/* fn main() {
    mut context := gg.new_context(
        bg_color:     gx.rgb(174, 198, 255)
        width:        600
        height:       400
        window_title: 'Polygons'
        frame_fn:     frame
    )
    context.run()
}

fn frame(mut ctx gg.Context) {
    ctx.begin()
    ctx.draw_convex_poly([f32(100.0), 100.0, 200.0, 100.0, 300.0, 200.0, 200.0, 300.0, 100.0, 300.0],
        gx.blue)
    ctx.draw_poly_empty([f32(50.0), 50.0, 70.0, 60.0, 90.0, 80.0, 70.0, 110.0], gx.black)
    ctx.draw_triangle_filled(450, 142, 530, 280, 370, 280, gx.red)
    ctx.end()
} */
