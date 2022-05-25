<?php

class Captcha {

  public function generate_code()
  {
    $chars    = '1234567890ABCDEF';   // Задаем символы, используемые в капче
    $length   = rand(4, 6);           // Задаем длину капчи
    $numChars = strlen($chars);
    $str      = '';
    for ($i = 0; $i < $length; $i++) {
        $str .= substr($chars, rand(1, $numChars) - 1, 1);
    } // Генерируем код
    
    // Перемешиваем, на всякий случай
    $array_mix = preg_split('//', $str, -1, PREG_SPLIT_NO_EMPTY);
    srand((float) microtime() * 1000000);
    shuffle($array_mix);
    // Возвращаем полученный код
    return implode("", $array_mix);
  }
  
  // функцию генерации изображения
  private function img_code($code) // $code - код капчи
  {
    // Отправляем браузеру Header'ы
    header("Expires: Mon, 26 Jul 1997 05:00:00 GMT");
    header("Last-Modified: " . gmdate("D, d M Y H:i:s", 10000) . " GMT");
    header("Cache-Control: no-store, no-cache, must-revalidate");
    header("Cache-Control: post-check=0, pre-check=0", false);
    header("Pragma: no-cache");
    header("Content-Type:image/png");
    // Задаем фоны для капчи
    $img_arr              = array(
        "1.png",
        "2.png",
        "3.png",
        "4.png",
        
    );
    // Шрифты для капчи. Задавать можно сколько угодно, они будут выбираться случайно
    $font = "3947.ttf"; // Имя шрифта

    // Генерируем "подстилку" для капчи со случайным фоном
    $img_dir = "./captcha/";
    $img_fn               = $img_arr[rand(0, sizeof($img_arr) - 1)];
    $im                   = imagecreatefrompng($img_dir . $img_fn);
    
    // Накладываем текст капчи                
    $x = rand(2, 7);
    for ($i = 0; $i < strlen($code); $i++) {
        $x += 42;
        $letter = substr($code, $i, 1);
        $color = imagecolorallocate($im, rand(0, 200), rand(0, 200), rand(0, 200));
        imagettftext($im, rand(20, 45), rand(2, 4), $x, rand(52, 70), $color, $img_dir . $font, $letter);
    }
    // Возвращаем получившееся изображение
    ImagePNG($im);
    ImageDestroy($im);
  }
  
  public function gen($captcha = "") {
    if($captcha === "")
        $captcha = $this->generate_code();
    $this->img_code($captcha); // Выводим изображение 
  }
  
}
