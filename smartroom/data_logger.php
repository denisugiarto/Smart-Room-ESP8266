<!DOCTYPE html>
<html lang="en">
<head>
	<?php 
		include("header.php"); 
	?>
	<title> Data Logger Sensor </title>
	<meta charset="UTF-8">
	<meta name="viewport" content="width=device-width, initial-scale=1">
	<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="css/style.css">
	<link rel="stylesheet" type="text/css" href="css/perfect-scrollbar.css">
	<link rel="stylesheet" type="text/css" href="css/main.css">
	<script src="js/jquery.min.js"></script>
	<script src="js/popper.js"></script>
	<script src="js/bootstrap.min.js"></script>
	<script src="js/select2.min.js"></script>
	<script src="js/perfect-scrollbar.min.js"></script>
	<script src="js/main.js"></script>
	
</head>
<body>
	<header id="header">
		<nav class="navbar navbar-fixed-top" role="banner">
			<div class="container">
				<div class="navbar-header">
                    <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-collapse">
                        <span class="sr-only">Toggle navigation</span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                        <span class="icon-bar"></span>
                    </button>
                    <a class="navbar-brand" href="index.html"> <img src="icon/logo.png" width="50" height="50"> SMART ROOM</a>
                </div>
				<div class="collapse navbar-collapse navbar-right">
					<ul class="nav navbar-nav">
						<li> <a href="index.php" title="Home"> Home</a></li>
						<li class="active" > <a href="data_logger.php" title="Data Logger"> Data Logger</a></li>
						<li> <a href="setting.php" title="Setting"> Setting</a></li>
					</ul>
				</div>
			</div>
		</nav>
	</header>
	<div id="chart" style="margin-top:100px">
		<div class="container">
					<?php include("data.php"); ?>
		</div>
	</div>
	<script>
		$('.js-pscroll').each(function(){
			var ps = new PerfectScrollbar(this);

			$(window).on('resize', function(){
				ps.update();
			})
		});
			
		
	</script>
	<?php include("footer.php"); ?>
</body>
</html>