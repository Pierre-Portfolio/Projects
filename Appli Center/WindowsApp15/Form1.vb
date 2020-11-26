Public Class Form1
    Dim LesCouleur As Color() = {Color.Red, Color.OrangeRed, Color.Orange, Color.Yellow, Color.GreenYellow, Color.LightGreen, Color.SpringGreen, Color.Turquoise, Color.DodgerBlue, Color.Blue, Color.MediumSlateBlue, Color.DarkViolet, Color.DeepPink}

    Public nbCouleur As Integer = LesCouleur.Length

    Dim compteur As Integer = 0

    Private Sub ChangerCouleurCollone4(laCouleur As Color)
        FondEscpace.BackColor = laCouleur
        biblio.ForeColor = laCouleur
    End Sub

    Private Sub ChangerCouleurCollone3(laCouleur As Color)
        leave.ForeColor = laCouleur
    End Sub

    Private Sub ChangerCouleurCollone2(laCouleur As Color)
        Jeux.ForeColor = laCouleur
        Codage.ForeColor = laCouleur
    End Sub

    Private Sub ChangerCouleurCollone1(laCouleur As Color)
        Musique.ForeColor = laCouleur
    End Sub

    Private Sub Form1_Load(sender As Object, e As EventArgs) Handles MyBase.Load
        Timer1.Enabled = True
    End Sub

    Private Sub Timer1_Tick(sender As Object, e As EventArgs) Handles Timer1.Tick

        ChangerCouleurCollone4(LesCouleur((compteur + 1) Mod nbCouleur))
        ChangerCouleurCollone3(LesCouleur(compteur Mod nbCouleur))
        ChangerCouleurCollone2(LesCouleur(compteur Mod nbCouleur))
        ChangerCouleurCollone1(LesCouleur(compteur Mod nbCouleur))
        compteur = compteur + 1


    End Sub

    Private Sub leave_Click(sender As Object, e As EventArgs) Handles leave.Click
        Dim result As Integer = MessageBox.Show("Voulez-vous vraiment quitter ?", "Alerte", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation)
        If result = DialogResult.No Then
            Exit Sub
        Else result = DialogResult.Yes
            Dispose()
        End If
    End Sub

    Private Sub Musique_Click(sender As Object, e As EventArgs) Handles Musique.Click
        Form2.Show()
        Me.Hide()
    End Sub

    Private Sub Jeux_Click(sender As Object, e As EventArgs) Handles Jeux.Click
        Form3.Show()
        Me.Hide()
    End Sub

    Private Sub Codage_Click(sender As Object, e As EventArgs) Handles Codage.Click
        Form4.Show()
        Me.Hide()
    End Sub
End Class
