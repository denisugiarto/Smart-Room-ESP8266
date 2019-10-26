<?php
$db_host = 'localhost'; // Nama Server
$db_user = 'root'; // User Server
$db_pass = ''; // Password Server
$db_name = 'iot'; // Nama Database

$conn = mysqli_connect($db_host, $db_user, $db_pass, $db_name);
if (!$conn) {
	die ('Gagal terhubung MySQL: ' . mysqli_connect_error());	
}

$sql = 'SELECT id, waktu, suhu, cahaya 
		FROM sensor ORDER BY id DESC LIMIT 30';
		
$query = mysqli_query($conn, $sql);

if (!$query) {
	die ('SQL Error: ' . mysqli_error($conn));
}

echo '	<div class="container-table100">
			<div class="wrap-table100">
				<div class="table100 ver1 m-b-110">
					<div class="table100-head">
						<table >
							<thead>
								<tr class="row100 head">
									<th style="text-align:center" class="cell100 column1">ID</th>
									<th class="cell100 column2">WAKTU</th>
									<th class="cell100 column3">SUHU</th>
									<th class="cell100 column4">CAHAYA</th>
								</tr>
							</thead>
						</table>
					</div>

					<div class="table100-body js-pscroll">
						<table>
							<tbody>';
		
while ($row = mysqli_fetch_array($query))
{
	echo '						<tr class="row100 body">
									<td style="text-align:center" class="cell100 column1">'.$row['id'].'</td>
									<td class="cell100 column2">'.$row['waktu'].'</td>
									<td class="cell100 column3">'.$row['suhu'].'</td>
									<td class="cell100 column4"">'.$row['cahaya'].'</td>
								</tr>';
}
echo '
							</tbody>
						</table>
					</div>
				</div>
			</div>
		</div>';
mysqli_free_result($query);
mysqli_close($conn);
?>