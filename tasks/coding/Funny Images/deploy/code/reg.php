<?php
session_start();
$limit=200;
$site = "Not robot!";
if (!isset($_SESSION['time'])) {
    $_SESSION['time'] = time();
}

if (!isset($_SESSION['count'])) {
    $_SESSION['count'] = 0;
}

if($_SESSION['time']+5 < time() && $_SESSION['count']<$limit )
{
	$l=$_SESSION['login'];
	$p=$_SESSION['pass'];
    session_unset();
    $_SESSION['time'] = time();
    $_SESSION['count'] = 0;
	$_SESSION['login']=$l;
	$_SESSION['pass']=$p;
    $_SESSION['load']=False;
}

if(isset($_POST['captha']) && $_POST['captha']!=="")
{
    if(isset($_SESSION['txt']) && $_SESSION['txt']===$_POST['captha']  )
    {
        $_SESSION['time'] = time();
        $_SESSION['count']++;
        $_SESSION['load']=False;
        unset($_SESSION['txt']);
        
    } else {
        $_SESSION['time'] = time();
        $_SESSION['count']=0;
        $_SESSION['load']=False;
    }
}

if($_SESSION['count']>=$limit ){
	if(isset($_POST['name']) && $_POST['name']!=="" && isset($_POST['pass']) && $_POST['pass']!=="") {
		$_SESSION['login']=$_POST['name'];
		$_SESSION['pass']=$_POST['pass'];
		$_SESSION['auth']=false;
		$message_s = "Successful registration";
		$_SESSION['time'] = time();
        $_SESSION['count']=0;
	} else {
		$message = "Now you can register. I know that you are not a robot.";
	}
}
?>

<!DOCTYPE html>
<html lang="en">
<head>
    <meta http-equiv="Content-Type" content="text/html; charset=UTF-8" />
    <title><?= $site ?></title>
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" type="text/css" href="/ui/uikitV3/css/uikit.min.css" />
    <script type='text/javascript' src='/ui/uikitV3/js/jquery-3.2.1.min.js'></script>
    <script type='text/javascript' src='/ui/uikitV3/js/uikit.min.js'></script>
    <script type='text/javascript' src='/ui/uikitV3/js/uikit-icons.js'></script>
</head>
<body>
    <? if($message!=null ){ ?>
        <script>
            UIkit.notification({
                message: '<?= $message ?>',
                status: 'primary'
            })
        </script>
    <? } ?>
    <? if($message_s!=null ){ ?>
        <script>
            UIkit.notification({
                message: '<?= $message_s ?>',
                status: 'success'
            })
        </script>
    <? } ?>
    <? if($message_w!=null ){ ?>
        <script>
            UIkit.notification({
                message: '<?= $message_w ?>',
                status: 'warning'
            })
        </script>
    <? } ?>
    <? if($message_d!=null ){ ?>
        <script>
            UIkit.notification({
                message: '<?= $message_d ?>',
                status: 'danger'
            })
        </script>
    <? } ?>
    <div class="uk-offcanvas-content">
        <div class="tm-header tm-header tm-header-transparent tm-header-overlay" uk-header>
            <div uk-sticky="{&quot;top&quot;: &quot;100vh&quot;, &quot;animation&quot;: &quot;uk-animation-slide-top&quot;, &quot;show-on-up&quot;: &quot;true&quot;}" media="768" cls-active="uk-navbar-sticky" sel-target=".uk-navbar-container">
                <div class=" uk-light uk-background-secondary uk-navbar-container" style="background-color: #0008;">
                    <div class="uk-container uk-container-expand uk-padding-remove-left">
                        <nav class="uk-navbar" uk-navbar>
                            <div class="uk-navbar-left">
                                <a href="/" class="uk-navbar-item uk-logo">
                                    <h1><?= $site ?></h1></a>
                            </div>
                            <div class="uk-navbar-right">
                                <ul class="uk-navbar-nav">
									<li>
										<a href="/" title="Home">Home</a>
									</li>
									<li>
										<a href="/auth.php" title="Log in">Log in</a>
									</li>
									<li class="uk-active">
										<a href="/reg.php" title="Register">Register</a>
									</li>
                                </ul>
                            </div>
                        </nav>
                    </div>
                </div>
            </div>
        </div>
        
		
		<div class="uk-section-default uk-position-relative uk-light" uk-scrollspy="{&quot;target&quot;:&quot;[uk-scrollspy-class]&quot;,&quot;cls&quot;:&quot;uk-animation-slide-bottom-small&quot;,&quot;delay&quot;:false}">
    <div style="background-image: url('/ui/img/bg.jpg'); background-color: #fff;" class="uk-background-norepeat uk-background-cover uk-background-center-center uk-section uk-flex uk-flex-middle" uk-height-viewport="offset-top: true">
        <div class="uk-position-cover" style="background-color: rgba(0, 0, 0, 0.5);"></div>
        <div class="uk-width-1-1">
            <div class="uk-container uk-position-relative">
                <div class="uk-margin" uk-grid>
                    <div class="uk-width-1-1@m">
                        <h1 class="uk-margin-medium uk-text-center uk-h1" uk-scrollspy-class>Registration</h1>
                    </div>
                    <form action="/reg.php" method="post" role="form" class="uk-flex-center uk-text-center uk-width-1-1 uk-first-column" uk-scrollspy-nav="closest: div; scroll: true; offset: 100">
						<?php if($_SESSION['count']>=$limit){?>
							<div class="uk-margin uk-align-center">
								<div class="uk-inline">
									<span class="uk-form-icon" uk-icon="icon: user"></span>
									<input class="uk-input uk-form-width-medium" type="text" name="name" <? isset($_POST['name'])?( 'value="'.$_POST['name']. '"'): '' ?>>
								</div>
							</div>
							<div class="uk-margin uk-align-center">
								<div class="uk-inline">
									<span class="uk-form-icon" uk-icon="icon: lock"></span>
									<input class="uk-input uk-form-width-medium" type="password" name="pass" <? isset($_POST['pass'])?( 'value="'.$_POST['pass']. '"'): '' ?>>
								</div>
							</div>
							<button class="uk-button uk-button-default uk-form-width-medium">Register</button>
						<?php } else { ?>
							<div class="uk-margin uk-align-center">
								Captcha <?= $_SESSION['count'] ?> of <?=$limit?>
							</div>
							<div class="uk-margin uk-align-center">
								<img src="/gen.php">
							</div>
							<div class="uk-margin uk-align-center">
								<div class="uk-inline">
									<span class="uk-form-icon" uk-icon="icon: lock"></span>
									<input class="uk-input uk-form-width-medium" name="captha">
								</div>
							</div>
							<button class="uk-button uk-button-default uk-form-width-medium">Submit</button>
						<?php } ?>
                    </form>
                </div>
            </div>
        </div>
    </div>
</div>
		
		
		
        <div id="page#-1" class="uk-section-secondary uk-section-small uk-section" uk-height-viewport="expand: true" style="box-sizing: border-box;">
            <div class="uk-container">
                <div class="uk-grid-large uk-grid-margin-large uk-grid" uk-grid>
                    <div class="uk-text-meta" uk-scrollspy-class>
                        <a href="/">AeroCTF</a>?? 2020
                        <br class="uk-visible@s">Any copying of materials, design elements without written permission is strictly prohibited!
                        <br> ???? ???????????????? ???????????????????????????? ???????????? ???? <span uk-icon="icon: telegram"></span> @Z_MIR1.
                    </div>
                    <div>
                        <a href="https://www.youtube.com/watch?v=dQw4w9WgXcQ">Get flag!</a>
                    </div>
                </div>
            </div>
        </div>
    </div>
    <style>
        .tm-header-overlay {
            position: absolute;
            z-index: 980;
            left: 0;
            right: 0;
        }
    </style>
</body>
</html>