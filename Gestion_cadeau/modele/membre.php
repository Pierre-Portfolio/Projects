<?php
class Membre {
	private $co;
	private $id;
	private $pseudo;
	private $email;
	private $passwd;
		
	public function __construct() {
	$cpt = func_num_args();
		$args = func_get_args();
		
		switch ($cpt) {
		case 3:
			$co = $args[0];
			$pseudo = $args[1];
			$mdp = $args[2];
			
			$result = mysqli_query ($co, "INSERT INTO membres values('','$pseudo','$mdp','$email')") OR die ("erreur");
			while($row = mysqli_fetch_assoc($result)){
				$this->co = $co;
				$this->pseudo = $pseudo;
				$this->mdp = $mdp;
				$this->id = $row["id"];
				$this->email = $row["email"]; break;
			}
		
		case 4:
			$co = $args[0];
			$pseudo = $args[1];
			$mdp = $args[2];
			$email = $args[3];
			
			$result = mysqli_query ($co, "SELECT id, email where pseudo='$pseudo' AND mdp = '$mdp'") OR die ("erreur");
			while($row = mysqli_fetch_assoc($result)) {
				$this->co = $co;
				$this->pseudo = $pseudo;
				$this->mdp = $mdp;
				$this->id = mysqli_insert_id($co);
				$this->email = $email; break;
			}
		}
	}
}

function connexion() {
	session_start();
	$_session['pseudo']= $this->pseudo;
}
		
function deconnexion() {
	session_destroy();
}

?>
