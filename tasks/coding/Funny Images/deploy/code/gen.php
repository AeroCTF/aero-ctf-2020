<?php
session_start();
include "captcha.php";
$captcha = new Captcha();

$limit=200;
if($_SESSION['time']+5 < time() && $_SESSION['count']<$limit || $_SESSION['load'])
{
	$l=$_SESSION['login'];
	$p=$_SESSION['pass'];
    session_unset();
    $_SESSION['time'] = time();
    $_SESSION['count'] = 0;
	$_SESSION['login']=$l;
	$_SESSION['pass']=$p;
}

$_SESSION['load']=True;
$_SESSION["txt"] = $captcha->generate_code();

$captcha->gen($_SESSION["txt"]);
