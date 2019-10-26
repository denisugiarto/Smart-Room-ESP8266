<!DOCTYPE html>
<html lang="en">
	<head>
	<?php 
		include("header.php"); 
	?>
	<title>Setting</title>
	<script type="text/javascript" src="js/jquery.min.js"></script>
	<script type="text/javascript" src="js/bootstrap-slider.js"></script>
	<script type="text/javascript" src="js/bootstrap.min.js"></script>
	<link rel="stylesheet" type="text/css" href="css/bootstrap.min.css">
	<link rel="stylesheet" type="text/css" href="css/bootstrap-slider.min.css">
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
						<li> <a href="index.php" title="Home"> Home</a></li>
						<li> <a href="data_logger.php" title="Data Logger"> Data Logger</a></li>
						<li class="active" > <a href="setting.php" title="Setting"> Setting</a></li>
					</ul>
				</div>
			</div>
		</nav>
	</header>	
	<div id="sett1" style="display:none">
		<div class="container" id="c1">
			<div class="row">
				<div class="header">
					Setting Aktuator
				</div>
				<div class="col-md-4" id="ak3">
					<div class="aktuator3">
						<h4> Proyektor</h4>
						<h1>
						<div id="aktuator3">...</div>
						</h1>
						<form action="/smartroom/api/aktuator/update3.php">
						<input id="ON2" type="Submit" class="btn-success" name="status" value="ON"/>
						<input id="OFF2"type="Submit" class="btn-danger" name="status" value="OFF"/>
						</form>
					</div>
				</div>
			</div>
		</div>
	</div>
	<div id="sett2" style="display:none">
		<div class="container" id="c2">
			<div class="row">
				<div class="header">
					Setting Sensor
				</div>
					
				<div class="col-md-6">
					<div class="aktuator1">
						<h4>Treshold Suhu</h4>
						<h1>
							<form action="/smartroom/api/kendali/thsuhu.php">
								<input id="ex7" name="batas" data-slider-id='ex1Slider' type="text" data-slider-min="0" data-slider-max="50" data-slider-step="1" data-slider-value="0"/>
								<button style="margin-left:50px" class="btn-info" type="input">Simpan</button>
							</form>
						</h1>
					</div>
				</div>
				
				<div class="col-md-6">
					<div class="aktuator2">
						<h4>Treshold Cahaya</h4>
						<h1>
							<form action="/smartroom/api/kendali/thcahaya.php">
								<input id="ex8" name="batas" data-slider-id='ex1Slider' type="text" data-slider-min="0" data-slider-max="1000" data-slider-step="5" data-slider-value="0"/>
								<button style="margin-left:50px" class="btn-info" type="input">Simpan</button>
							</form>
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
     				var temper=(data['TRESHOLD'][Object.keys(data['TRESHOLD'])]['suhu']);
                   	var light =(data['TRESHOLD'][Object.keys(data['TRESHOLD'])]['cahaya']);				
					$("#ex7").slider({
						value: temper,
						tooltip: 'always'	
					});
					$("#ex8").slider({
						value: light,
						tooltip: 'always'
					});
					var ak3=(data['AKTUATOR'][(Object.keys(data['AKTUATOR'])[2])]['status']);
					document.getElementById("aktuator3").innerHTML = ak3;
					if (ak3 == 'ON'){
						document.getElementById('ON2').style.display = 'none';
						document.getElementById('OFF2').style.display = 'block';
						$("#OFF2").css({"margin" : "0 auto 10px auto"});
					}
					if (ak3 == 'OFF'){
						document.getElementById('ON2').style.display = 'block';
						document.getElementById('OFF2').style.display = 'none';
						$("#ON2").css({"margin" : "0 auto 10px auto"});
					}
					document.getElementById('sett1').style.display = 'block';
					document.getElementById('sett2').style.display = 'block';
					$("#c1").css({"min-width":"175px", "max-width":"25%"});
					$("#ak3").attr('class','col-md-12');
					$("#btnM").css({"margin":"0 auto 10px auto"});
					$("#sett1").css({"margin-top":"100px"});
					$("#sett2").css({"margin-top":"50px"});
				});
		}

        window.setInterval(function(){
			loaddata();
        }, 3000);
			
	</script>
	<?php include("footer.php"); ?>	
    </body>
</html>