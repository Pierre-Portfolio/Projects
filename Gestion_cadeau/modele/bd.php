<?php
	class Bd{
		private $co;
		private $host;
		private $user;
		private $Bdd;
		private $passwd;
		
		public function __construct($bdd){
			$this->host="localhost";
			$this->user="admin";
			$this->passwd="admin";
			$this->Bdd="$Bdd"; // le nom de votre base de données
		}
		
		public function connexion() {
			$this->$co = mysqli_connect($this->host , $this->user , $this->passwd, $this->Bdd) or
			die("erreur de connexion");
			return $this->co;
		}
		
		public function deconnexion(){
		mysqli_close($this->co);
		}
	}
?>	
		
