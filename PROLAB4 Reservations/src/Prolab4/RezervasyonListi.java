package Prolab4;

public class RezervasyonListi {
	Rezervasyon RootRz;
	int RezervasyonSayisi;
	
	RezervasyonListi(){
		this.RootRz=null;
		this.RezervasyonSayisi=0;
	}
	RezervasyonListi(Rezervasyon RootRz){
		this.RootRz=RootRz;
	}

	public void addRezervasyon(Rezervasyon Rz) {
		if(Rz!=null) {

			if(this.RootRz==null) {
				RootRz=Rz;
			}
			else {
				Rezervasyon sonRz=null;
				Rezervasyon tempRz=RootRz;
				while(tempRz.getNextRezervasyon()!=null) {
					tempRz=tempRz.getNextRezervasyon();
				}
				sonRz=tempRz;
				sonRz.nextRezervasyon=Rz;
				this.RezervasyonSayisi++;
			}
			//System.out.println("eklendi");
		}	
	}

	public void RezervasyonOlustur(String[] splitted) {

		Rezervasyon Rz=new Rezervasyon();
		Rz.setYerId(splitted[1].trim());
		Rz.setRezervasyonZamani(splitted[2].trim());
		Rz.setEnlem(splitted[3].trim());
		Rz.setBoylam(splitted[4].trim());
		Rz.setSehir(splitted[5].trim());

		if(Rz!=null)
			addRezervasyon(Rz);


	}

	public void RezervasyonListele() {
		if(this.RootRz==null) {
			//No Rezervasyon there
		}	
		else {
			Rezervasyon tempRz=RootRz;
			while(tempRz!=null) {
				//REZERVASYONUN BILGILERI YAZDIR 
				System.out.println("YerId: "+tempRz.getYerId());
				System.out.println("Rz zamani: "+tempRz.getRezervasyonZamani());
				System.out.println("Enlem: "+tempRz.getEnlem());
				System.out.println("Boylam:"+tempRz.getBoylam());
				System.out.println("Sehir :"+tempRz.getSehir());
				System.out.println("--------");
				tempRz=tempRz.getNextRezervasyon();
			}
		}
	}

}
