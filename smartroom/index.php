<!DOCTYPE html>
<html lang="en">
	<head>
	<?php 
		include("header.php");
	?>
	<title>Home</title>
	<script type="text/javascript" src="js/jquery.min.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="css/style.css">
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
						<li class="active" > <a href="index.php" title="Home"> Home</a></li>
						<li> <a href="data_logger.php" title="Data Logger"> Data Logger</a></li>
						<li> <a href="setting.php" title="Setting"> Setting</a></li>
					</ul>
				</div>
			</div>
		</nav>
	</header>
	<div id="content1">
		<div class="container">
			<div class="row">
				<div class="header">
					Kondisi Ruangan
				</div>
				<div class="col-md-6">
					<div class="sensor1">
						<h4> Suhu</h4>
						<h1>
						<a id="suhu"> ... </a>
						<a> &deg; C </a>
						</h1>
					</div>
				</div>
				<div class="col-md-6">
					<div class="sensor2">
						<h4> Pencahayaan </h4>
						<h1>
						<a id="cahaya"> ... </a>
						<a> Lux </a>
						</h1>
					</div>
				</div>
			</div>
		</div>
	</div>
	
	<div id="content2" style="margin-bottom: 50px">
		<div class="container">
			<div class="row">
				<div class="header">
					Kondisi Aktuator
				</div>
				<div class="col-md-4">
					<div class="aktuator1">
						<h4> Kipas Angin </h4>
						<h1>
						<div id="aktuator1">...</div>
						</h1>
					</div>
				</div>
				<div class="col-md-4">
					<div class="aktuator2">
						<h4> Lampu</h4>
						<h1>
						<div id="aktuator2">...</div>
						</h1>
					</div>
				</div>
				<div class="col-md-4">
					<div class="aktuator3">
						<h4> Proyektor</h4>
						<h1>
						<div id="aktuator3">...</div>
						</h1>
					</div>
				</div>
			</div>
		</div>
	</div>
	
	<script>
		window.onload = function() {
            loaddata();
        };

		function loaddata(){
				var url = "http://<?php echo $ip?>/smartroom/api/api.php";
				$.getJSON(url, function(data) {
                    var val= data;
                   	var temper=(data['SENSOR'][Object.keys(data['SENSOR'])]['suhu']);
                  	var light=(data['SENSOR'][Object.keys(data['SENSOR'])]['cahaya']);
                   	document.getElementById("suhu").innerHTML = temper;
                   	document.getElementById("cahaya").innerHTML = light;

                   	var ak1=(data['AKTUATOR'][(Object.keys(data['AKTUATOR'])[0])]['status']);
					var ak2=(data['AKTUATOR'][(Object.keys(data['AKTUATOR'])[1])]['status']);
					var ak3=(data['AKTUATOR'][(Object.keys(data['AKTUATOR'])[2])]['status']);
                   	document.getElementById("aktuator1").innerHTML = ak1;
					document.getElementById("aktuator2").innerHTML = ak2;
					document.getElementById("aktuator3").innerHTML = ak3;
					document.getElementById('content1').style.display = 'block';
					document.getElementById('content2').style.display = 'block';
				});
				
		}
		
        window.setInterval(function(){
        loaddata();
            }, 500);
	
	</script>

	<?php include("footer.php"); ?>
	
    </body>
</html>