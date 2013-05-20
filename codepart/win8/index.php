﻿<!DOCTYPE>
<html>
<head>
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<title>likebeta Personal Center</title>
<link href="http://fonts.googleapis.com/css?family=Goudy+Bookletter+1911:400" rel="stylesheet" type="text/css" />
<link rel="stylesheet" type="text/css" href="style.css"/>
<link rel="shortcut icon" href="images/favicon.ico" />
<script src="http://lib.sinaapp.com/js/jquery/1.4.1/jquery.min.js" type="text/javascript"></script>
<link href="artDialog/skins/twitter.css" rel="stylesheet" />
<script src="artDialog/artDialog.min.js"></script>
<script type="text/javascript">
$(document).ready(function(){
	$("img").mouseover(function(){
		$(this).animate({opacity:"0.5"})}).mouseout(function(){$(this).animate({opacity:"1"});
	});
});
</script>
</head>
<body>
<div id="header">
	<h1>likebeta Personal Center</h1>
	<h2>Dream is Doomed Lonely Journey</h2>
</div>
<!-- #header end  -->
<div id="content">
	<div class="row">
		<div class="item_small"><a href="http://weibo.com/likebeta" title="My Sina Microblog" target="_blank"><img src="images/sina-weibo.png" alt="Sina Microblog" /></a></div>
		<div class="item_small"><a href="https://twitter.com/likebeta" title="Following my Twitter" target="_blank"><img src="images/twitter.png" alt="Twitter" /></a></div>
		<div class="item_big"><a href="http://www.ixxoo.me" title="Visit My Blog" target="_blank"><img src="images/blog.png" alt="Blog" /></a></div>
		<div class="item_small"><a href="https://www.facebook.com/messycode" title="Visit My Facebook" target="_blank"><img src="images/facebook.png" alt="Facebook" /></a></div>
	</div>

	<div class="row">
		<div class="item_small"><a href="http://mail.qq.com/cgi-bin/qm_share?t=qm_mailme&email=GnZzcX94f257WmtrNHl1dw" title="Email Me" target="_blank"><img src="images/mail.png" alt="Email" /></a></div>
		<div class="item_big"><a href="http://app.ixxoo.me/list.php" title="likebeta Application Series" target="_blank"><img src="images/apps.png" alt="Application Series" /></a></div>
		<div class="item_small"><a href="https://plus.google.com/106237727629335165345" title="My Google plus" target="_blank"><img src="images/google-plus.png" alt="Google+" /></a></div>
		<div class="item_small"><a href="http://t.qq.com/likebeta" title="Tencent Weibo" target="_blank"><img src="images/tencent-weibo.png" alt="About Me" /></a></div>
	</div>

	<div class="row">
		<div class="item_middle coming"><a href="http://www.ixxoo.me/about.html" title="About Me" target="_blank"><img src="images/me.png" alt="About Me" /></a></div>
		<div class="item_small"><a href="http://sighttp.qq.com/authd?IDKEY=3858148ba014b4fde1fa40c51515cb05b2db607dc871510f" title="Contact Me with QQ" target="_blank"><img src="images/qq.png" alt="QQ" /></a></div>
		<div class="item_big"><a href="https://github.com/likebeta" title="Github"  target="_blank"><img src="images/github.png" alt="Github" /></a></div>
	</div>
</div>
<!-- #content end  -->
<div class="clear"></div>

<div id="footer">
	<div id="copyright">Copyright &copy; 2013 likebeta, All Rights Reserved</div>
	<div id="statistics"></div>
</div>
<!-- #footer end  -->
<script type="text/javascript">
$(document).ready(function(){
  $(".coming").bind("click",function(){
   art.dialog({
      title:"likebeta Cloud Center",
      lock: true,
      background: '#600', 
      icon: 'error',
      content: '<p>Sorry, access forbidden!</p><p>You can contact me for more support.</p>'
  });
  return false;});
});
</script>
</body>
</html>
