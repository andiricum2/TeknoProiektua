import time

AteaPosizioa = 0
Denbora = 1

def AtearenPosizioaKalkulatu(mota):
    global AteaPosizioa
    if mota == "Ireki":
        AteaPosizioa = 90
    elif mota == "Itxi":
        AteaPosizioa = 0

class Prozesuak:
    @staticmethod
    def AteaIreki():
        print("Atea Irekitzen")
        AtearenPosizioaKalkulatu(mota="Ireki")
        time.sleep(Denbora)
        print("Atea Irekita")
        print(f"Atearen Posizioa: {AteaPosizioa}º")

    @staticmethod
    def KotxeaDago():
        print("Kotxea dagoen detektatzen")
        time.sleep(Denbora)
        print("Atea Itxita")
        print(f"Atearen Posizioa: {AteaPosizioa}º")

    @staticmethod
    def AteaItxi():
        print("Atea Ixten")
        AtearenPosizioaKalkulatu(mota="Itxi")
        time.sleep(Denbora)
        print("Atea Itxita")
        print(f"Atearen Posizioa: {AteaPosizioa}º")


mota = input("Zer nahi dezu egin? (Ireki/Itxi): ")
if mota.lower() in ["ireki", "itxi"]:
    AtearenPosizioaKalkulatu(mota)
    if mota.lower() == "ireki":
        Prozesuak.AteaIreki()
    else:
        Prozesuak.AteaItxi()
else:
    print("Ezin da hau egin.")
