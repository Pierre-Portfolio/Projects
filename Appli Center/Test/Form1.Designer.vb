<Global.Microsoft.VisualBasic.CompilerServices.DesignerGenerated()>
Partial Class Form1
    Inherits System.Windows.Forms.Form

    'Form remplace la méthode Dispose pour nettoyer la liste des composants.
    <System.Diagnostics.DebuggerNonUserCode()>
    Protected Overrides Sub Dispose(ByVal disposing As Boolean)
        Try
            If disposing AndAlso components IsNot Nothing Then
                components.Dispose()
            End If
        Finally
            MyBase.Dispose(disposing)
        End Try
    End Sub

    'Requise par le Concepteur Windows Form
    Private components As System.ComponentModel.IContainer

    'REMARQUE : la procédure suivante est requise par le Concepteur Windows Form
    'Elle peut être modifiée à l'aide du Concepteur Windows Form.  
    'Ne la modifiez pas à l'aide de l'éditeur de code.
    <System.Diagnostics.DebuggerStepThrough()>
    Private Sub InitializeComponent()
        Me.components = New System.ComponentModel.Container()
        Dim resources As System.ComponentModel.ComponentResourceManager = New System.ComponentModel.ComponentResourceManager(GetType(Form1))
        Me.Jeux = New System.Windows.Forms.Button()
        Me.Timer1 = New System.Windows.Forms.Timer(Me.components)
        Me.Codage = New System.Windows.Forms.Button()
        Me.leave = New System.Windows.Forms.Button()
        Me.FondEscpace = New System.Windows.Forms.Panel()
        Me.biblio = New System.Windows.Forms.Button()
        Me.Musique = New System.Windows.Forms.Button()
        Me.FondEscpace.SuspendLayout()
        Me.SuspendLayout()
        '
        'Jeux
        '
        Me.Jeux.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Jeux.BackgroundImage = CType(resources.GetObject("Jeux.BackgroundImage"), System.Drawing.Image)
        Me.Jeux.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Jeux.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Jeux.Location = New System.Drawing.Point(28, 139)
        Me.Jeux.Name = "Jeux"
        Me.Jeux.Size = New System.Drawing.Size(113, 57)
        Me.Jeux.TabIndex = 1
        Me.Jeux.Text = "Jeux"
        Me.Jeux.UseVisualStyleBackColor = True
        '
        'Timer1
        '
        '
        'Codage
        '
        Me.Codage.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Codage.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.images
        Me.Codage.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Codage.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Codage.Location = New System.Drawing.Point(146, 139)
        Me.Codage.Name = "Codage"
        Me.Codage.Size = New System.Drawing.Size(113, 57)
        Me.Codage.TabIndex = 2
        Me.Codage.Text = "Codage"
        Me.Codage.UseVisualStyleBackColor = True
        '
        'leave
        '
        Me.leave.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.leave.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.leave.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.leave.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.leave.Location = New System.Drawing.Point(28, 202)
        Me.leave.Name = "leave"
        Me.leave.Size = New System.Drawing.Size(232, 33)
        Me.leave.TabIndex = 3
        Me.leave.Text = "Quitter"
        Me.leave.UseVisualStyleBackColor = True
        '
        'FondEscpace
        '
        Me.FondEscpace.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.FondEscpace.Controls.Add(Me.biblio)
        Me.FondEscpace.Location = New System.Drawing.Point(27, 12)
        Me.FondEscpace.Name = "FondEscpace"
        Me.FondEscpace.Size = New System.Drawing.Size(232, 51)
        Me.FondEscpace.TabIndex = 87
        '
        'biblio
        '
        Me.biblio.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.biblio.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.biblio.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.biblio.Location = New System.Drawing.Point(1, 3)
        Me.biblio.Name = "biblio"
        Me.biblio.Size = New System.Drawing.Size(229, 46)
        Me.biblio.TabIndex = 0
        Me.biblio.Text = "         BIBLIOTHEQUE            CENTER"
        Me.biblio.UseVisualStyleBackColor = True
        '
        'Musique
        '
        Me.Musique.Anchor = CType((((System.Windows.Forms.AnchorStyles.Top Or System.Windows.Forms.AnchorStyles.Bottom) _
            Or System.Windows.Forms.AnchorStyles.Left) _
            Or System.Windows.Forms.AnchorStyles.Right), System.Windows.Forms.AnchorStyles)
        Me.Musique.BackgroundImage = Global.WindowsApp15.My.Resources.Resources.sky_night_space_813269
        Me.Musique.Font = New System.Drawing.Font("Microsoft Sans Serif", 11.25!, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, CType(0, Byte))
        Me.Musique.ForeColor = System.Drawing.SystemColors.ActiveCaptionText
        Me.Musique.Location = New System.Drawing.Point(28, 100)
        Me.Musique.Name = "Musique"
        Me.Musique.Size = New System.Drawing.Size(232, 33)
        Me.Musique.TabIndex = 88
        Me.Musique.Text = "AudioVisuel"
        Me.Musique.UseVisualStyleBackColor = True
        '
        'Form1
        '
        Me.AutoScaleDimensions = New System.Drawing.SizeF(6.0!, 13.0!)
        Me.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font
        Me.BackgroundImage = Global.WindowsApp15.My.Resources.Resources._4494276_galaxy_wallpapers_hd
        Me.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Stretch
        Me.ClientSize = New System.Drawing.Size(284, 262)
        Me.Controls.Add(Me.Musique)
        Me.Controls.Add(Me.FondEscpace)
        Me.Controls.Add(Me.leave)
        Me.Controls.Add(Me.Codage)
        Me.Controls.Add(Me.Jeux)
        Me.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedToolWindow
        Me.Icon = CType(resources.GetObject("$this.Icon"), System.Drawing.Icon)
        Me.Name = "Form1"
        Me.Text = "Bibliotheque d'application"
        Me.TransparencyKey = System.Drawing.Color.Transparent
        Me.FondEscpace.ResumeLayout(False)
        Me.ResumeLayout(False)

    End Sub

    Friend WithEvents Jeux As Button
    Friend WithEvents Timer1 As Timer
    Friend WithEvents Codage As Button
    Friend WithEvents leave As Button
    Friend WithEvents FondEscpace As Panel
    Friend WithEvents biblio As Button
    Friend WithEvents Musique As Button
End Class
