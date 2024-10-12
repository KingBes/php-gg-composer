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

    

    public function newContext(array $options): \FFI\CData
    {
        $config = $this->ffi->new("struct Config");
        $config->width = 600;
        $config->height = 600;
        var_dump($config);
        if (!isset($options["width"]) && is_int($options["width"])) {

        }
        return $this->ffi->new_context($config);
    }

    public function run(\FFI\CData $context): void
    {
        $this->ffi->run($context);
    }
}

$gg = new Gg;

$context = $gg->newContext([]);

$gg->run($context);
