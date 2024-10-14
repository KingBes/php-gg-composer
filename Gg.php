<?php

// 严格模式
declare(strict_types=1);

class Gg
{
    public \FFI $ffi;

    public function __construct()
    {
        $header_content = file_get_contents(__DIR__ . DIRECTORY_SEPARATOR . "Gg.h");
        $library_file = __DIR__ . DIRECTORY_SEPARATOR . "gg.dll";
        $this->ffi = \FFI::cdef($header_content, $library_file);
    }

    /**
     * 转v字符串 function
     *
     * @param string $str
     * @return \FFI\CData
     */
    protected function toString(string $str): \FFI\CData
    {
        return $this->ffi->to_string($str);
    }

    /**
     * 颜色 function
     *
     * @param integer $r
     * @param integer $g
     * @param integer $b
     * @param float $a
     * @return \FFI\CData
     */
    public function color(int $r, int $g, int $b, float $a = 0): \FFI\CData
    {
        return $this->ffi->to_color($r, $g, $b, $a);
    }

    /**
     * 窗口函数 function
     *
     * @param Closure $frameFn
     * @return mixed
     */
    public function frameFn(\Closure $frameFn): mixed
    {
        $c_fn = $this->ffi->new("void (*)(void*)");
        $c_fn = function ($ctx) use ($frameFn) {
            return $frameFn($ctx);
        };
        return $c_fn;
    }

    /**
     * 验证配置 function
     *
     * @param array $options
     * @return \FFI\CData
     */
    protected function options(array $options): \FFI\CData
    {
        $config = $this->ffi->new("struct Config");
        // 验证 宽度
        if (isset($options["width"]) && is_int($options["width"])) {
            $config->width = $options["width"];
        } else {
            throw new \Exception("数组键'width'必须是'int'且不可为空。\nThe array key 'width' must be 'int' and cannot be null.");
        }

        // 验证 高度
        if (isset($options["height"]) && is_int($options["height"])) {
            $config->height = $options["height"];
        } else {
            throw new \Exception("数组键'height'必须是'int'且不可为空。\nThe array key 'height' must be 'int' and cannot be null.");
        }

        // 验证窗口标题
        if (isset($options["window_title"]) && is_string($options["window_title"])) {
            $config->window_title = $this->toString($options["window_title"]);
        } else {
            $config->window_title = $this->toString("世界上最好的语言");
        }

        // 验证 font_size
        if (isset($options["font_size"]) && !is_int($options["font_size"])) {
            throw new \Exception("数组键'font_size'必须是'int'。\nArray key 'font_size' must be 'int'.");
        }

        if (isset($options["bg_color"]) && is_object($options["bg_color"])) {
            $config->bg_color = $options["bg_color"];
        } else if (!is_object($options["bg_color"])) {
            throw new \Exception("数组键'bg_color'必须是'\FFI\CData'。\nArray key 'bg_color' must be '\FFI\CData'.");
        }

        if (isset($options["frame_fn"]) && is_object($options["frame_fn"])) {
            $config->frame_fn = $options["frame_fn"];
        } else if (!is_object($options["frame_fn"])) {
            throw new \Exception("数组键'frame_fn'必须是'frameFn'。\nArray key 'frame_fn' must be 'frameFn'.");
        }

        var_dump($config);

        return $config;
    }

    /**
     * 创建上下文 function
     *
     * @param array $options
     * @return \FFI\CData
     */
    public function newContext(array $options): \FFI\CData
    {
        return $this->ffi->new_context($this->options($options));
    }

    /**
     * 准备用于绘制的上下文 function
     *
     * @param \FFI\CData $context
     * @return void
     */
    public function begin(\FFI\CData $context): void
    {
        $this->ffi->begin($context);
    }

    /**
     * 运行 function
     *
     * @param \FFI\CData $context
     * @return void
     */
    public function run(\FFI\CData $context): void
    {
        $this->ffi->run($context);
    }
}

$gg = new Gg;

$context = $gg->newContext([
    "width" => 800,
    "height" => 600,
    "bg_color" => $gg->color(0, 255, 255, 1),
    "frame_fn" => $gg->frameFn(function ($ctx){
        // var_dump($ctx);
        $ctx->begin($this);
    })
]);

$gg->run($context);
